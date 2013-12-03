#include "LCD.h"
#include "game.h"
//#include "graphics_tm4c123.h"
//#include "PLL.h"

int main(){
    PLL_Init();
    LCD_Init();
    /*cube temp = {{{0, MIN_INT + 100, 0}, {50, MIN_INT + 100, 0},
            {0, MIN_INT + 50, 0},{50, MIN_INT + 50, 0}, 
            {0, MIN_INT + 100, 50}, {50, MIN_INT + 100, 50},
            {0, MIN_INT + 50, 50}, {50, MIN_INT + 50, 50}}, 0 }; 
    add_cube(temp);
    render_cubes();
    */
    LCD_SetTextColorRGB(0xFFFF);
    out_int(9);
    return 0;
}
