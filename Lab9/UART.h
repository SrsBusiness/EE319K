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
 
 // standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F
 
//------------UART1_Init------------
// Initialize the UART for 100,000 baud rate (assuming 80 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART1_Init(void);
void UART1_enable_int(); 
 //------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(unsigned char data);
unsigned char UART1_InChar();

 
 


