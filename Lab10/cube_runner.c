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
    systick_init();
    LCD_ColorFill(0xFFFF);
    
    cube this_cube;
    point temp;
    for(int j = 0; j < 2; j++){
        temp = (point){j * 80, focal_point.y + 800, -239};
        new_cube(temp, 0, &this_cube);
        add_cube(this_cube);
    }
    render_cubes(BLACK, RED);
    draw_player();
        //i++;
    //}
    while(1);
}
