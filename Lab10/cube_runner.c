#include "LCD.h"
#include "game.h"
#include "graphics_tm4c123.h"
#include "PLL.h"
#include "LCD.h"

int main(){
    PLL_Init();
    LCD_Init();
    LCD_ColorFill(0xFFFF);
    int x = MIN_INT;
    int i = 0;
    cube temp;
    add_cube(temp);
    while(1){
        render_cubes(); 
        erase_cubes();
        cubes[0] = (cube){{{0, x + i / 10 + 100 + 200, -239}, {50, x + i / 10 + 100 + 200, -239},
                {50, x + i / 10 + 50 + 200, -239},{0, x + i / 10 + 50 + 200, -239}, 
                {0, x + i / 10 + 100 + 200, 50 - 239}, {50, x + i / 10 + 100 + 200, 50 - 239},
                {50, x + i / 10 + 50 + 200, 50 - 239}, {0, x + i / 10 + 50 + 200, 50 - 239}}, 0 }; 
        i++;
    }
    return 0;
}
