/*
 * File:   adc.c
 * Author: Alexandru
 *
 * Created on November 10, 2015, 2:29 PM
 */


#include <xc.h>
#include "adc.h"
unsigned LED_Output = 0;	//assigned to LED PORT to light
								//connected LEDs

void Initialize(void)
{
	//Configure Port:
	//Disable pin output driver (See TRIS register)
	TRISBbits.TRISB4 = 1;
	// Configure pin 0 of PORTA as analog input
	ANSEL = 0x01;
    TRISA = 0xFF;
	//Configure RC0, RC1, RC2 and RC3 as digital output
	TRISD = 0x00;

	//Configure the ADC module:
	//Select ADC conversion clock Frc
	ADCON1bits.ADCS = 0b11;

	//Configure voltage reference using VDD
	ADCON0bits.VCFG = 0;
	//Select ADC input channel pin RA0 - potentiometer on Pickit2 debug express (AN0)
	ADCON0bits.CHS = 0b000;
	//Select result format right justified: result 2 MSB bits in ADRESH and 8 bits in ADRESL
	ADCON0bits.ADFM = 1;
	//Turn on ADC module
	ADCON0bits.ADON = 1;
}
	
/*----------------------------------------------------------
	Subroutine: Get_Inputs
	Parameters: none
	Returns:	nothing
	Synopsys:	Obtains all off-chip inputs
----------------------------------------------------------*/
void Get_Inputs(void)
{
	//Perform an ADC of potentiometer connected to pin 13
	//Wait the required acquisition time
	__delay_ms(1);
	//Start conversion by setting the GO/DONE bit.
	ADCON0bits.GO_nDONE = 1;
	//Wait for ADC conversion to complete
	//Polling the GO/DONE bit
	// 0 = ADC completed
	// 1 = ADC in progress
	while(ADCON0bits.GO_nDONE == 1);
}

/*----------------------------------------------------------
	Subroutine: Decide
	Parameters: none
	Returns:	nothing
	Synopsys:	Function that calls all sub-routines for 
				processing the input data
----------------------------------------------------------*/
void Decide(void)
{
	//Assign the upper 4 bits of ADRESH to the lower 4 bits
	//of LED_Output
	LED_Output = ADRESL;
								//to the right
}

/*----------------------------------------------------------
	Subroutine: Do_Outputs
	Parameters: none
	Returns:	nothing
	Synopsys:	Ouputs to off-chip circuitry based off of
				Decide function
----------------------------------------------------------*/
void Do_Outputs(void)
{
	//Assign contents of LED_Output to PORTD to light the connected
	//LEDs
	PORTD = LED_Output;
}

unsigned getADCValue()
{
    return LED_Output;
}

/*----------------------------------------------------------
	Subroutine: Timing
	Parameters: none
	Returns:	nothing
	Synopsys:	Controls the how fast code in the main() is executed 
----------------------------------------------------------*/
void Timing(void)

{
	//ADD TIMING CODE HERE
}