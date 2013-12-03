#include "game.h"
#include "graphics_tm4c123.h"
void systick_handler(){
    render();
    if(collision()){
        // game over
    }
    focal_point.y += dy;
    focal_point.x += dx;
}

void right_button_pressed(){
    if(dx = speed)
        dx = 0;
    else
        dx = speed;
}

void left_button_pressed(){
    if(dx = -1 * speed)
        dx = 0;
    else
        dx = -1 * speed;
}


