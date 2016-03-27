/* 
 * File:   pwm.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void PWM1_init(unsigned long freq);
void PWM2_init(unsigned long freq);

void PWM1_start();
void PWM2_start();
void PWM2_init30k();
void PWM2_init7k();
void PWM1_stop();
void PWM2_stop();

void PWM2_duty(unsigned int duty);
void PWM1_duty(unsigned int duty);

void PWM2_duty_percent(unsigned char duty);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

