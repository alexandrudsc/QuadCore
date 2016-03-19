#include "bldc.h"

char state = SPEED_NOT_CHANGING;

// motor speed in rpms
int motor_speed = 0;

char direction = FORWARD;

volatile int commut_freq = 0;

void set_motor_speed(int speed) {
    if (speed < motor_speed)
        deccelerate_to(speed);
    else
        accelerate_to(speed);
}

void motor_dir(char dir) {
    direction = dir;
    switch (dir) {
        case FORWARD:
            break;
        case BACKWARDS:
            break;
        default:
            return;
    }
}

// speed in rpms
static void accelerate_to(int speed) {
    commut_freq = speed;
    state = SPEED_CHANGING;
}

// speed in rpms
static void deccelerate_to(int speed) {
    commut_freq = speed;
    state = SPEED_CHANGING;
}

void motor_break() {
    all_low();
    motor_speed = 0;
}

void motor_go_forward() {
    delay_milis(commut_freq);
    phase_A();
    delay_milis(commut_freq);
    phase_B();
    delay_milis(commut_freq);
    phase_C();
    delay_milis(commut_freq);
}

void motor_go(int speed) {
    delay_milis(speed);
    phase_A();
    delay_milis(speed);
    phase_B();
    delay_milis(speed);
    phase_C();

}

void motor_go_back() {
    delay_milis(commut_freq);
    phase_C();
    delay_milis(commut_freq);
    phase_B();
    delay_milis(commut_freq);
    phase_A();
}

static void all_low() {
    A_HIGH = 0;
    A_LOW = 0;

    B_HIGH = 0;
    B_LOW = 0;

    C_HIGH = 0;
    C_LOW = 0;
}

static void phase_A() {
    all_low();
    A_HIGH = 1;
    B_LOW = 1;
}

static void phase_B() {
    all_low();
    B_HIGH = 1;
    C_LOW = 1;
}

static void phase_C() {
    all_low();
    C_HIGH = 1;
    A_LOW = 1;
}

/*  delay between phase commutation.
 * if the speed is changed, cancel the delay
*/
static void delay_milis(int milis) {
    for (int i = 1; i < milis; i++)
        if (state == SPEED_CHANGING) {
            state = SPEED_NOT_CHANGING;
            break;
        } else
            __delay_ms(1);
}

static void delay_micros(int micros) {
    for (int i = 1; i < micros; i++)
        __delay_us(1);
}