/* 
 * File: uc_config.h
 * Author: Alexandru
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_CONFIG_H
#define	XC_CONFIG_H

// internal frequency after reset 4MHZ
#define _XTAL_FREQ 8000000

// timer prescaler for pwm 
#define TMR2PRESCALE 4

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

#endif	/* XC_HEADER_TEMPLATE_H */

