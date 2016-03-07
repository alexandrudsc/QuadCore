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
// CONFIG1
#pragma config FOSC = HS       // Oscillator Selection Bits (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

volatile unsigned char duty = 0;

void main(void) {

    //unsigned int adc_value;

    //init_adc(); //Initialize the relevant registers for ADC

    PORTD = 0; // all leds turn off

    i2c_init_slave();

    PWM2_init(1000); // init pwm2 registers with 1 kHz. pwm2 output is on pin RD2 (pin 21))
    PWM2_duty(0); // first duty cycle value; it will be changed
    PWM2_start();

    while (1) {
        //adc_value = get_adc_value();   // get the value of ADC 
        //duty = (float)adc_value/ 255 * 1023;
        PWM2_duty_percent(duty);
    }

}

// handler for all interrupts. We use it only for I2C events
interrupt void ISR_Handler(void) {

    // SSP interrupts (i2c)
    if (SSPIF) {

        duty = i2c_read_byte();

        SSPIF = 0; // Clear the interrupt flag.
        //SSP_Handler();			// Do I2C communication // TODO
    }
}
