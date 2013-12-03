#include "LCD.h"
#include "game.h"
#include "graphics_tm4c123.h"
#include "PLL.h"
#include "LCD.h"
#include "ADC.h"
//point player[3] = {{focal_point.x - 7, 200 + focal_point.y, -239}, 
//{focal_point.x + 7, 200 + focal_point.y, -239}, 
//{focal_point.x, 203 + focal_point.y, -239}};
int main(){
    PLL_Init();
    LCD_Init();
    LCD_ColorFill(0xFFFF);
    int x = MIN_INT;
    int i = 0;
    
    //while(1){
       // render_cubes(BLACK, 0xF800); 
        //render_cubes(WHITE, WHITE);
    /*add_cube((cube){{{0, x + i / 10 + 100 + 200, -239}, {50, x + i / 10 + 100 + 200, -239},
                {50, x + i / 10 + 50 + 200, -239},{0, x + i / 10 + 50 + 200, -239}, 
                {0, x + i / 10 + 100 + 200, 50 - 239}, {50, x + i / 10 + 100 + 200, 50 - 239},
                {50, x + i / 10 + 50 + 200, 50 - 239}, {0, x + i / 10 + 50 + 200, 50 - 239}}, 0 });    
    */    
    cube this_cube;
    point temp;
    for(int j = 0; j < 10; j++){
        temp = (point){j * 30, focal_point.y + 300, -239};
        new_cube(temp, 0, &this_cube);
        add_cube(this_cube);
    }
    render_cubes(BLACK, RED);
    draw_player();
        //i++;
    //}
    return 0;
}
