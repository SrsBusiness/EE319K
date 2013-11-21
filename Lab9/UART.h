#define UART1_DR_R              (*((volatile unsigned long *)0x4000D000))
 #define UART1_RSR_R             (*((volatile unsigned long *)0x4000D004))
 #define UART1_ECR_R             (*((volatile unsigned long *)0x4000D004))
 #define UART1_FR_R              (*((volatile unsigned long *)0x4000D018))
 #define UART1_ILPR_R            (*((volatile unsigned long *)0x4000D020))
 #define UART1_IBRD_R            (*((volatile unsigned long *)0x4000D024))
 #define UART1_FBRD_R            (*((volatile unsigned long *)0x4000D028))
 #define UART1_LCRH_R            (*((volatile unsigned long *)0x4000D02C))
 #define UART1_CTL_R             (*((volatile unsigned long *)0x4000D030))
 #define UART1_IFLS_R            (*((volatile unsigned long *)0x4000D034))
 #define UART1_IM_R              (*((volatile unsigned long *)0x4000D038))
 #define UART1_RIS_R             (*((volatile unsigned long *)0x4000D03C))
 #define UART1_MIS_R             (*((volatile unsigned long *)0x4000D040))
 #define UART1_ICR_R             (*((volatile unsigned long *)0x4000D044))
 #define UART1_DMACTL_R          (*((volatile unsigned long *)0x4000D048))
 #define UART1_9BITADDR_R        (*((volatile unsigned long *)0x4000D0A4))
 #define UART1_9BITAMASK_R       (*((volatile unsigned long *)0x4000D0A8))
 #define UART1_PP_R              (*((volatile unsigned long *)0x4000DFC0))
 #define UART1_CC_R              (*((volatile unsigned long *)0x4000DFC8))
 
#define GPIO_PORTC_DATA_BITS_R  ((volatile unsigned long *)0x40006000)
 #define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
 #define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
 #define GPIO_PORTC_IS_R         (*((volatile unsigned long *)0x40006404))
 #define GPIO_PORTC_IBE_R        (*((volatile unsigned long *)0x40006408))
 #define GPIO_PORTC_IEV_R        (*((volatile unsigned long *)0x4000640C))
 #define GPIO_PORTC_IM_R         (*((volatile unsigned long *)0x40006410))
 #define GPIO_PORTC_RIS_R        (*((volatile unsigned long *)0x40006414))
 #define GPIO_PORTC_MIS_R        (*((volatile unsigned long *)0x40006418))
 #define GPIO_PORTC_ICR_R        (*((volatile unsigned long *)0x4000641C))
 #define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
 #define GPIO_PORTC_DR2R_R       (*((volatile unsigned long *)0x40006500))
 #define GPIO_PORTC_DR4R_R       (*((volatile unsigned long *)0x40006504))
 #define GPIO_PORTC_DR8R_R       (*((volatile unsigned long *)0x40006508))
 #define GPIO_PORTC_ODR_R        (*((volatile unsigned long *)0x4000650C))
 #define GPIO_PORTC_PUR_R        (*((volatile unsigned long *)0x40006510))
 #define GPIO_PORTC_PDR_R        (*((volatile unsigned long *)0x40006514))
 #define GPIO_PORTC_SLR_R        (*((volatile unsigned long *)0x40006518))
 #define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
 #define GPIO_PORTC_LOCK_R       (*((volatile unsigned long *)0x40006520))
 #define GPIO_PORTC_CR_R         (*((volatile unsigned long *)0x40006524))
 #define GPIO_PORTC_AMSEL_R      (*((volatile unsigned long *)0x40006528))
 #define GPIO_PORTC_PCTL_R       (*((volatile unsigned long *)0x4000652C))
 #define GPIO_PORTC_ADCCTL_R     (*((volatile unsigned long *)0x40006530))
 #define GPIO_PORTC_DMACTL_R     (*((volatile unsigned long *)0x40006534))
 
 
 void UART_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 50;                    // IBRD = int(80,000,000 / (16 * 100,000)) = int(50)
  UART0_FBRD_R = 0;                     // FBRD = int(0 * 64 ) = 0
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PC1-0
  GPIO_PORTC_DEN_R |= 0x03;             // enable digital I/O on PC1-0
                                        // configure PC1-0 as UART
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTC_AMSEL_R &= ~0x03;          // disable analog functionality on PC
}



