#include "LCD.h"
#include "game.h"
#include "graphics_tm4c123.h"
#include "PLL.h"
#include "LCD.h"
#include "ADC.h"
#include "interrupts.h"
//point player[3] = {{focal_point.x - 7, 200 + focal_point.y, -239}, 
//{focal_point.x + 7, 200 + focal_point.y, -239}, 
//{focal_point.x, 203 + focal_point.y, -239}};
int main(){
    PLL_Init();
    LCD_Init();
    LCD_ColorFill(0xFFFF);
    cube this_cube;
    point temp;
    for (int k = 0; k < 1; k++) {
        for(int j = 0; j < 5; j++){
            temp = (point){j * 80, focal_point.y + k*1000+400, -239};
            new_cube(temp, 0, &this_cube);
            add_cube(this_cube);
        }
    }
	button_init();
    systick_init();
	EnableInterrupts();
    // timer2_init(0x145855);
    while(1);
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
