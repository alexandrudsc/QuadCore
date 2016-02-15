/*
 * File:   main.c
 * Author: Alexandru
 *
 * Created on November 10, 2015, 2:18 PM
 */


#include <xc.h>
#include "adc.h"
#include "pwm.h"
// CONFIG1
#pragma config FOSC = HS       // Oscillator Selection Bits (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

void main(void) {
    
    unsigned int adc_value, duty;
    
    init_adc(); //Initialize the relevant registers
    
    PORTD = 0x0;    // all leds turn off
    
    
    PWM2_Init(1000); // init pwm registers with 1 kHz
    PWM2_Duty(200);  // first duty cycle value; it will be changed
    PWM2_Start();   
    
    while (1) {
        get_inputs();           // wait for ADC to finish conversion
        decide();               // store the value of the ADC
        adc_value = get_adc_value();   // get the value of ADC 
        duty = (float)adc_value/ 255 * 1023;
        PWM2_Duty( duty );
    }

}
