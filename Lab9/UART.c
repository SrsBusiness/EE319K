#include "UART.h"
#include "tm4c123gh6pm.h"
#include "ADC.h"
#include "FIFO.h"

void UART1_Init(void){
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
	UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	UART1_IBRD_R = 50;                    // IBRD = int(80,000,000 / (16 * 100,000)) = int(50)
	UART1_FBRD_R = 0;                     // FBRD = int(0 * 64 ) = 0
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
	UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
	GPIO_PORTC_AFSEL_R |= 0x03;           // enable alt funct on PC1-0
	GPIO_PORTC_DEN_R |= 0x03;             // enable digital I/O on PC1-0
										// configure PC1-0 as UART
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTC_AMSEL_R &= ~0x03;          // disable analog functionality on PC	
}
void UART1_enable_int(){
	UART1_IM_R |= 0x10;
	UART1_IFLS_R &= 0x10;
	UART1_IFLS_R &= ~0x28;
	NVIC_PRI1_R &= 0xE00000;
	NVIC_EN0_R  &= 0x40;
}
void UART1_OutChar(unsigned char data) {
	while((UART1_FR_R & UART_FR_TXFF));
	UART1_DR_R = data;
}

void UART1_Handler(){
	UART1_ICR_R = 0x10;
	PF2 ^= 0x04;
	while(!(UART_FR_RXFE & 0x0010)){
		FIFO_put(UART1_DR_R);
	}
}
/*
unsigned char UART1_InChar(void){
	while((UART1_FR_R & 0x0010));
	return (unsigned char)(UART1_DR_R & 0xFF);
}
*/