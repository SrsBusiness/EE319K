#include "LCD.h"
#include "game.h"
#include "graphics_tm4c123.h"
#include "PLL.h"
#include "LCD.h"
#include "ADC.h"
#include "interrupts.h"
#include "Lab6.h"
//point player[3] = {{focal_point.x - 7, 200 + focal_point.y, -239}, 
//{focal_point.x + 7, 200 + focal_point.y, -239}, 
//{focal_point.x, 203 + focal_point.y, -239}};
int main(){
    PLL_Init();
    LCD_Init();
    LCD_ColorFill(BLACK);
	Sound_Init();
	button_init();
    ADC_Init();
	
	Timer0A_Init(33332);
	//timer2_init();
	EnableInterrupts();
    //timer2_init(0x145855);
    while(!game_over);
	playSong(fairyFountain, FAIRY_FOUNTAIN_LENGTH);
    //render_cubes(BLACK, RED);
    
        //i++;
    //}
    /*int i = 0;
    LCD_OutString("Start\n");
    while(i++ < 6000){
        render_cubes(BLACK, RED);
        render_cubes(WHITE, WHITE);
    }
    LCD_OutString("End\n");*/
}
