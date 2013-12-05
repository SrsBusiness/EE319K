// Piano.c
// This software configures the off-board piano keys
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

// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void Piano_Init(void){ 
	SYSCTL_RCGC2_R |= 0x04;
	__nop();
	__nop();
	GPIO_PORTC_DEN_R |= 0x0F;
	GPIO_PORTC_DIR_R &= ~0x0F;
	GPIO_PORTC_AMSEL_R = 0;
}
// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
unsigned long Piano_In(void){ 
	return GPIO_PORTC_DATA_R & 0x0F;
}
