// Lab8.c
// Runs on LM4F120 or TM4C123
// Use the SysTick timer to request interrupts at a particular period.
// Put your name here or look very silly
// Put the date here or look very silly

// Analog Input connected to PE2=ADC1
// displays on Kentec EB-LM4F120-L35
// PF1 SysTick toggle


#include "lcd.h"
#include "pll.h"
#include "ADC.h"
#include "tm4c123gh6pm.h"

unsigned long ADCMail;
unsigned char ADCStatus;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
int main2();
int main3();

void PortF_Init(void){
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= 0x20;
	GPIO_PORTF_DEN_R |= 0x04;
	GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_AFSEL_R = 0;
}
unsigned long Data;      // 12-bit ADC
unsigned long Position;  // 32-bit fixed-point 0.001 cm
int main2(void){      // single step this program and look at Data
	PLL_Init();         // Bus clock is 80 MHz 
	ADC_Init();         // turn on ADC, set channel to 1
	while(1){                
		Data = ADC_In();  // sample 12-bit channel 1
	}
	//return main2();
}

int main4(void){
	PLL_Init();         // Bus clock is 80 MHz 
	ADC_Init();         // turn on ADC, set channel to 1
	LCD_Init();   
	LCD_SetTextColorRGB(YELLOW);
	PortF_Init();
	while(1){           // use scope to measure execution time for ADC_In and LCD_OutDec           
		PF2 = 0x04;       // Profile
		Data = ADC_In();  // sample 12-bit channel 1
		PF2 = 0x00;       // Profile
		LCD_Goto(0,0);
		LCD_OutDec(Data); 
		LCD_OutString("    "); 
	}
}

unsigned long Convert(unsigned long input){
	return 2 * input / 5;
}
int main3(void){ 
	PLL_Init();        // Bus clock is 80 MHz 
	LCD_Init();   
	LCD_SetTextColorRGB(YELLOW);
	PortF_Init();
	ADC_Init();        // turn on ADC, set channel to 1
	while(1){  
		PF2 ^= 0x04;     // Heartbeat
		Data = ADC_In(); // sample 12-bit channel 1
		PF2 ^= 0x04;
	}
}   

int main(){
	PLL_Init();        // Bus clock is 80 MHz 
	LCD_Init();   
	LCD_SetTextColorRGB(YELLOW);
	PortF_Init();
	ADC_Init();        // turn on ADC, set channel to 1
	while(1){  
		Position = Convert(ADCMail); 
		LCD_Goto(0,0);
		LCD_OutString("Position: "); 
		LCD_OutFix(Position);
		LCD_OutString(" cm");
	}
}
