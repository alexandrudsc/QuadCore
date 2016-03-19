/* 
 * File:   pwm.h
 * Author: 
 * Comments: Header file for PWM management for PIC16f917 (only two PWM modules available)
 *  * PWM operation from datasheet:
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
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PWM_H
#define	PWM_H

#include <xc.h> // include processor files - each processor file is guarded.  

// init CCP modules for PWM output
void PWM1_init(unsigned long freq);
void PWM2_init(unsigned long freq);

// start PWM generators
void PWM1_start();
void PWM2_start();

// stop PWM generators
void PWM1_stop();
void PWM2_stop();

// set the PWM duty by writing directly to CCP registers
void PWM2_duty(unsigned int duty);
void PWM1_duty(unsigned int duty);

// set the PWM duty by percent value
void PWM2_duty_percent(unsigned char duty);
void PWM1_duty_percent(unsigned char duty);

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* PWM_H */

