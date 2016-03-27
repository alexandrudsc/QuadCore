/*
 * File:   pwm.c
 * Author: Alexandru
 *
 * Created on November 10, 2015, 3:55 PM
 * Has functions for initializing, starting/ stoping PWM output for two CCP (Capture - Compare - PWM ) modules of PIC16f917
 * PWM operation from datasheet:
        The following steps should be taken when configuring 
        the CCP module for PWM operation:
            1. Set the PWM period by writing to the PR2
            register.
            2. Set the PWM duty cycle by writing to the
            CCPR1L register and CCP1CON<5:4> bits.
            3. Make the RC5/T1CKI/CCP1/SEG10 pin an
            output by clearing the TRISC<5> bit.
            4. Set the TMR2 prescale value and enable Timer2
            by writing to T2CON.
            5. Configure the CCP1 module for PWM operation
 */

#include "uc_config.h"
#include "pwm.h"

unsigned long freq;

/*----------------------------------------------------------
	Subroutine: PWM1_init
	Parameters: fre - the PWM frequency
	Returns:	nothing
	Synopsys:	PR2 register specifies the PWM period like below: 
                PWM period = (PR2) + 1] * 4 * TOSC * (TMR2 prescale value)
                The PWM frequency is: freq = 1/period.
                _XTAL_FREQ - internal clock ( "uc_config.h" )
----------------------------------------------------------*/
void PWM1_init(unsigned long fre) {
    PR2 = (_XTAL_FREQ / (fre * 4 * TMR2PRESCALE)) - 1;
    freq = fre;
}

// PWM 9bits resolution at 7khz & 40%duty
void PWM2_init7k(){
    PR2 = 0b01000110 ;
    T2CON = 0b00000101 ;
    CCPR1L = 0b00011100 ;
    CCP1CON = 0b00011100 ;
}


void PWM2_init(unsigned long fre) {
    PR2 = (_XTAL_FREQ / (fre * 4 * TMR2PRESCALE)) - 1;
    freq = fre;
}


/* The PWM duty cycle is defined as this:
 * PWM duty cycle =(CCPR1L:CCP1CON<5:4>) * TOSC * (TMR2 prescale value)
 * PWM duty has 10 bit resolution. 
 */
void PWM1_duty(unsigned int duty) {
  
    // duty is 10 bit value
    if (duty > 1023) 
        duty = 1023;
    if (duty < 0)
        duty = 0;
    CCP1X = duty & 2;
    CCP1Y = duty & 1;
    CCPR1L = duty >> 2;
}

void PWM2_duty(unsigned int duty) { 
    // duty is 10 bit value
    if (duty > 1023) 
        duty = 1023;
    if (duty < 0)
        duty = 0;
                
    CCP2X = duty & 2;
    CCP2Y = duty & 1;
    CCPR2L = duty >> 2;
}

// set duty of PWM using percentage (0% - 100%)
void PWM2_duty_percent(unsigned char duty){
    PWM2_duty( ((float)duty / 100) * 1023 );
}

/*
 * 
 */
void PWM1_start() {
    CCP1M3 = 1;
    CCP1M2 = 1;
#if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
    TRISC2 = 0;
}

void PWM1_stop() {
    CCP1M3 = 0;
    CCP1M2 = 0;
}

void PWM2_start() {
    CCP2M3 = 1;
    CCP2M2 = 1;
#if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
    TRISC1 = 0;
}

void PWM2_stop() {
    CCP2M3 = 0;
    CCP2M2 = 0;
}

