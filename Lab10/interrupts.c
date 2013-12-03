#include "game.h"
#include "graphics_tm4c123.h"
#include "LCD.h"
#include "tm4c123gh6pm.h"

void systick_init(){
    NVIC_ST_CTRL_R = 0;  //disable systick during initialization
    NVIC_ST_RELOAD_R = 0x145855;    //maximum reload value
    NVIC_ST_CURRENT_R = 0;   //any write to current clears it
    NVIC_ST_CTRL_R = 7;  //enable systick with core clock
}
void systick_handler(){
    LCD_OutChar('a');
    render_cubes(WHITE, WHITE);
    render_cubes(BLACK, RED);
    focal_point.y += dy;
    focal_point.x += dx;
}

void right_button_pressed(){
    if(dx == speed)
        dx = 0;
    else
        dx = speed;
}

void left_button_pressed(){
    if(dx == -1 * speed)
        dx = 0;
    else
        dx = -1 * speed;
}

void change_speed(){
    //stuff
}
