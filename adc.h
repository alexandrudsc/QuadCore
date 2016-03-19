/* 
 * File:   adc.h
 * Author: Alexandru
 * Comments:
 * Header file for ADC utilities. We can read the digital value after the A/D conversion on
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H  

#include "uc_config.h"

// init ADC0 module
void init_adc(void);

// wait for A/D conversion to finish
void get_input(void);

void decide(void);

// get the digital value from a specific Analog input pin 
unsigned short adc_channel(int);

// flash leds
void do_outputs(void);
void timing(void);
unsigned get_adc_value();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* ADC_H */

