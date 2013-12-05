// Sound.c, 
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Section 1-2pm     TA: Saugata Bhattacharyya
// Lab number: 6
// Hardware connections
#include "tm4c123gh6pm.h"
#include "dac.h"
// put code definitions for the software (actual C code)
// this file explains how the module works
#define SAMPLES 32
#define CLOCK 80000000
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
int table[SAMPLES] = {8, 9, 10, 12, 13, 14, 14, 15, 
					15, 15, 14, 14, 13, 12, 10, 9, 
					8, 6, 5, 3, 2, 1, 1, 0, 
					0, 0, 1, 1, 2, 3, 5, 6};
int tableSquare[SAMPLES] = {15, 15, 15, 15, 15, 15, 15, 15, 
					15, 15, 15, 15, 15, 15, 15, 15, 
					0, 0, 0, 0, 0, 0, 0, 0, 
					0, 0, 0, 0, 0, 0, 0, 0};
/*
int tableHorn[SAMPLES] = {7, 
8, 
8, 
8,
8,
9,
10,
12,
15,
15,
15,
13,
10,
7,
4,
3,
3,
3,
3,
3,
3,
3,
4,
4,
4,
4,
5,
6,
7,
8,
8,
9,
9,
10,
11,
11,
12,
13,
13,
12,
12,
13,
14,
12,
11,
9,
8,
6,
3,
2,
1,
1,
0,
1,
1,
1,
2,
2,
3,
4,
4,
6,
7,
7,
};
int tableFlute[SAMPLES] = {6,
7,
9,
9,
10,
11,
12,
13,
13,
14,
15,
15,
15,
15,
15,
14,
13,
13,
12,
11,
10,
9,
8,
7,
7,
6,
6,
5,
5,
5,
5,
4,
4,
4,
4,
4,
4,
3,
3,
3,
3,
3,
2,
2,
1,
1,
1,
1,
0,
0,
0,
0,
0,
0,
1,
1,
1,
2,
2,
3,
3,
4,
4,
5,
};
*/
unsigned long currentPeriod = 0;
int current = 0;
/*
	T in ns, f in Hz
	f = 1 / T
	Reload = CLOCK / f / SAMPLES = CLOCK / (1 / T) / SAMPLES
*/
void Sound_Init(unsigned long period){
	SYSCTL_RCGC2_R |= 0x20;
	__nop();
	__nop();
	GPIO_PORTF_DEN_R |= 0x04;
	GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_AMSEL_R = 0;
	
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 7;
	DAC_Init();
}

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none
void Sound_Play(unsigned long period){
	if(!period){
		NVIC_ST_RELOAD_R = 0x00FFFFFF;
		currentPeriod = 0;
	}else{
		NVIC_ST_RELOAD_R = period / (0x3B9ACA00 / CLOCK) / SAMPLES - 1;
		currentPeriod = 1;
	}
}



// Interrupt service routine
// Executed every periodically
void systick_handler(void){
	GPIO_PORTD_DATA_R |= 0x10;
	if(currentPeriod){
		DAC_Out(table[current]);
		current = ++current % SAMPLES;
	}
	GPIO_PORTF_DATA_R ^= 0x04;
	GPIO_PORTD_DATA_R &= ~0x10;
}
