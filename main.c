/*
 * File:   main.c
 * Author: Alexandru
 *
 * Created on November 10, 2015, 2:18 PM
 */


#include <xc.h>
#include "adc.h"
#include "pwm.h"
#include "i2c.h"
#include "bldc.h"

// CONFIG
#pragma config FOSC = HS       // Oscillator Selection Bits (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

volatile unsigned char duty = 0;

// handler for i2c input message
void i2c_in_handler(MESSAGE_IN* msg_in);

//Handler for an i2c output request, i.e. the master wants to read from slave
void i2c_out_handler(MESSAGE_OUT* msg_out);

void main(void) {
    
    OSCCONbits.IRCF  = 7; //111 => internal OSC 8 MHZ
    
    //unsigned int adc_value;
    
    unsigned int start = 100;
    
    init_adc(); //Initialize the relevant registers for ADC

    PORTD = 0x00; // all leds turn off

    // set handler for a complete i2c input message
    i2c_set_handler_in(&i2c_in_handler);
    
    // set handler for a complete i2 message output request
    i2c_set_handler_out(&i2c_out_handler);
    
    i2c_init_slave();
    
    //PWM2_init(1000); // init pwm2 registers with 1 kHz. pwm2 output is on pin RD2 (pin 21))
    //PWM2_duty(255); // first duty cycle value; it will be changed
    PWM2_init7k();
//    PWM2_start();;
    
    set_motor_speed(1000);
    
    while (1) {
//        get_inputs();
//        decide();
//        unsigned int adc_value = adc_channel(0);   // get the value of ADC 
//        duty = (float)adc_value/ 255 * 10 23;
//        PWM2_duty(adc_value);
//        adc_value = 1023 - adc_value;
//        set_motor_speed(adc_value);
//        motor_go_forward();
    }

}

/*
 * Handler for an i2c input message
 */
void i2c_in_handler(MESSAGE_IN* msg_in){
    
    PORTD = 0xFF;

    // set frequency of PWM
    PWM2_init(msg_in->PWM_FREQ_BYTE1 << 8 + msg_in->PWM_FREQ_BYTE2);
    
    // set duty of PWM
    PWM2_duty(msg_in->PWM_DUTY_BYTE1 << 8 + msg_in->PWM_DUTY_BYTE2);
            
    // set motor direction
    
    // set the speed of motor
    set_motor_speed(msg_in->MOTOR_SPEED_BYTE1 << 8 + msg_in->MOTOR_SPEED_BYTE2);

}

/*
 * Handler for an i2c output request, i.e. the master wants to read from slave
 */
void i2c_out_handler(MESSAGE_OUT* msg_out){
    msg_out->nr_bytes = 5;
    msg_out->DISTANCE_BYTE1 = 'A';
    msg_out->DISTANCE_BYTE2 = 'B';
    msg_out->DISTANCE_BYTE3 = 'a';
    msg_out->DISTANCE_BYTE4 = 'b';
}