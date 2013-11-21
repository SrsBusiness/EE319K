#include "UART.h"
#include "tm4c123gh6pm.h"
 

void UART1_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 50;                    // IBRD = int(80,000,000 / (16 * 100,000)) = int(50)
  UART1_FBRD_R = 0;                     // FBRD = int(0 * 64 ) = 0
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTC_AFSEL_R |= 0x03;           // enable alt funct on PC1-0
  GPIO_PORTC_DEN_R |= 0x03;             // enable digital I/O on PC1-0
                                        // configure PC1-0 as UART
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTC_AMSEL_R &= ~0x03;          // disable analog functionality on PC
}
