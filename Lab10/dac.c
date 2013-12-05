// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Section 1-2pm     TA: Saugata Bhattacharyya
// Lab number: 6
// Hardware connections

#include "tm4c123gh6pm.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	SYSCTL_RCGC2_R |= 0x08;
	__nop();
	__nop();
	GPIO_PORTD_DEN_R |= 0x3F;
	GPIO_PORTD_DIR_R |= 0x3F;
	GPIO_PORTD_AMSEL_R &= 0x00;
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
	GPIO_PORTD_DATA_R = data & 0x3F;
}

