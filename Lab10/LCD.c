#include "tm4c123gh6pm.h"
#include "LCD.h"

#define va_list __builtin_va_list
#define va_arg __builtin_va_arg
#define va_start __builtin_va_start
#define va_end __builtin_va_end

void LCD_GPIOInit(){
    SYSCTL_RCGC2_R |= 0x03;
    __nop();
	__nop();
	__nop();
    GPIO_PORTA_DEN_R |= 0xF0;
    GPIO_PORTA_DIR_R |= 0xF0;
    GPIO_PORTA_AFSEL_R = 0;
    GPIO_PORTA_DATA_R |= 0xF0;
    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_DIR_R |= 0xFF;
    GPIO_PORTB_AFSEL_R = 0;
}

void LCD_WriteCommand(unsigned char command){
    GPIO_PORTB_DATA_R = 0;
    GPIO_PORTA_DATA_R = 0x10;
    GPIO_PORTA_DATA_R = 0x70;
    GPIO_PORTB_DATA_R = command;
    GPIO_PORTA_DATA_R = 0x10;
    __nop();
	__nop();
	__nop();
    GPIO_PORTA_DATA_R = 0xF0;
}

void LCD_WriteData(unsigned short data){
    GPIO_PORTB_DATA_R = (data >> 8);
    GPIO_PORTA_DATA_R = 0x50;
    GPIO_PORTA_DATA_R = 0x70;
    GPIO_PORTB_DATA_R = data & 0x00FF;
    GPIO_PORTA_DATA_R = 0x50;
    __nop();
	__nop();
	__nop();
    GPIO_PORTA_DATA_R = 0xF0;
}

// stdio functions

int out_int(int i){
    if(i < 0){
        LCD_OutChar('-');
        i *= -1;
    }
    char stack[10];
    char index = 0;
    char digits;
    while(i){
        stack[index++] = i % 10;
        i /= 10;
    }
    digits = index;
    while(index){
        LCD_OutChar('0' + stack[--index]);
    }
    return digits;
}

