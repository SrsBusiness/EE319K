// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0 SS3 to be triggered by
// software and trigger a conversion, wait for it to finish,
// and return the result.
// Put your name here or look very silly
// Put the date here or look very silly


#include "tm4c123gh6pm.h"
#include "ADC.h"

// This initialization function 
// Max sample rate: <=125,000 samples/second
// Sequencer 0 priority: 1st (highest)
// Sequencer 1 priority: 2nd
// Sequencer 2 priority: 3rd
// Sequencer 3 priority: 4th (lowest)
// SS3 triggering event: software trigger
// SS3 1st sample source: Ain1 (PE2)
// SS3 interrupts: flag set on completion but no interrupt requested
void ADC_Init(void){ 
	//make it PE2 and channel 1
	SYSCTL_RCGC2_R |= 0x00000010;   // 1) activate clock for Port E
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
        GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
	GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alt funct on PE2
	GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
	GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog funct on PE2
	SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0 
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	SYSCTL_RCGC0_R &= ~0x00000300;  // 7) 125kHz ADC conversion speed 
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	ADC0_SSPRI_R = 0x0123;          // 8) Seq 3 is highest priority
	ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
	ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1; // 11) Ain9 (PE4)
	ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
	ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
	/*
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 1999999;			// (0.025 s * 80000000)-1
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 7;
	*/
	
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC_In(void){  
	unsigned long result;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R&0x08) == 0);
	ADC0_ISC_R = 0x0008;
	result = ADC0_SSFIFO3_R & 0xFFF;
	return result;
}




