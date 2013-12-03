#include "graphics_tm4c123.h"
#include "game.h"
#include "LCD.h"

#define WIDTH 320 
#define HEIGHT 240
#define BLACK 0x0000
#define WHITE 0xFFFF

#define v(a) vertices[a]

#define swap(a, b) do{int i = a; a = b; b = i;} while(0)

void print_int(int, char, char);
void render_cubes(){
    projected_cube temp;
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 8; j++){
            temp.vertices[j] = project(cubes[i].vertices[j]);
        }
        LCD_DrawLine(temp.vertices[0].x, temp.vertices[0].y, 
                temp.vertices[1].x, temp.vertices[1].y, 0);
        LCD_DrawLine(temp.vertices[0].x, temp.vertices[0].y, 
                temp.vertices[3].x, temp.vertices[3].y, 0);
        LCD_DrawLine(temp.vertices[0].x, temp.vertices[0].y, 
                temp.vertices[4].x, temp.vertices[4].y, 0);
        
        LCD_DrawLine(temp.vertices[1].x, temp.vertices[1].y, 
                temp.vertices[5].x, temp.vertices[5].y, 0);
        LCD_DrawLine(temp.vertices[1].x, temp.vertices[1].y, 
                temp.vertices[2].x, temp.vertices[2].y, 0);
        LCD_DrawLine(temp.vertices[2].x, temp.vertices[2].y, 
                temp.vertices[6].x, temp.vertices[6].y, 0);
        LCD_DrawLine(temp.vertices[2].x, temp.vertices[2].y, 
                temp.vertices[3].x, temp.vertices[3].y, 0);
        LCD_DrawLine(temp.vertices[3].x, temp.vertices[3].y, 
                temp.vertices[7].x, temp.vertices[7].y, 0);
        LCD_DrawLine(temp.vertices[4].x, temp.vertices[4].y, 
                temp.vertices[5].x, temp.vertices[5].y, 0);
        LCD_DrawLine(temp.vertices[4].x, temp.vertices[4].y, 
                temp.vertices[7].x, temp.vertices[7].y, 0);
        LCD_DrawLine(temp.vertices[5].x, temp.vertices[5].y, 
                temp.vertices[6].x, temp.vertices[6].y, 0);
        LCD_DrawLine(temp.vertices[6].x, temp.vertices[6].y, 
                temp.vertices[7].x, temp.vertices[7].y, 0);
    }
}
void erase_cubes(){
    projected_cube temp;
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 8; j++){
            temp.vertices[j] = project(cubes[i].vertices[j]);
        }
        LCD_DrawLine(temp.vertices[0].x, temp.vertices[0].y, 
                temp.vertices[1].x, temp.vertices[1].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[0].x, temp.vertices[0].y, 
                temp.vertices[3].x, temp.vertices[3].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[0].x, temp.vertices[0].y, 
                temp.vertices[4].x, temp.vertices[4].y, 0xFFFF);
        
        LCD_DrawLine(temp.vertices[1].x, temp.vertices[1].y, 
                temp.vertices[5].x, temp.vertices[5].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[1].x, temp.vertices[1].y, 
                temp.vertices[2].x, temp.vertices[2].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[2].x, temp.vertices[2].y, 
                temp.vertices[6].x, temp.vertices[6].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[2].x, temp.vertices[2].y, 
                temp.vertices[3].x, temp.vertices[3].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[3].x, temp.vertices[3].y, 
                temp.vertices[7].x, temp.vertices[7].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[4].x, temp.vertices[4].y, 
                temp.vertices[5].x, temp.vertices[5].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[4].x, temp.vertices[4].y, 
                temp.vertices[7].x, temp.vertices[7].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[5].x, temp.vertices[5].y, 
                temp.vertices[6].x, temp.vertices[6].y, 0xFFFF);
        LCD_DrawLine(temp.vertices[6].x, temp.vertices[6].y, 
                temp.vertices[7].x, temp.vertices[7].y, 0xFFFF);
    }
}
/*
void render_cube(cube object, unsigned short color){
    projected_cube p_temp;
    for(int i = 0; i < 8; i++){
        p_temp.vertices[j] = project(object.vertices[j]);
    }

    LCD_DrawLine(p_temp.v(0).x, p_temp.v(0).y, 
                 p_temp.v(1).x, p_temp.v(1).y, color);
    LCD_DrawLine(p_temp.v(0).x, p_temp.v(0).y, 
                 p_temp.v(3).x, p_temp.v(3).y, color);
    LCD_DrawLine(p_temp.v(0).x, p_temp.v(0).y, 
                 p_temp.v(4).x, p_temp.v(4).y, color);

    LCD_DrawLine(p_temp.v(2).x, p_temp.v(2).y, 
                 p_temp.v(1).x, p_temp.v(1).y, color);
    LCD_DrawLine(p_temp.v(2).x, p_temp.v(2).y, 
                 p_temp.v(3).x, p_temp.v(3).y, color);
    LCD_DrawLine(p_temp.v(2).x, p_temp.v(2).y, 
                 p_temp.v(6).x, p_temp.v(6).y, color);
   
    LCD_DrawLine(p_temp.v(5).x, p_temp.v(5).y, 
                 p_temp.v(1).x, p_temp.v(1).y, color);
    LCD_DrawLine(p_temp.v(5).x, p_temp.v(5).y, 
                 p_temp.v(4).x, p_temp.v(4).y, color);
    LCD_DrawLine(p_temp.v(5).x, p_temp.v(5).y, 
                 p_temp.v(6).x, p_temp.v(6).y, color);
   
    LCD_DrawLine(p_temp.v(7).x, p_temp.v(7).y, 
                 p_temp.v(3).x, p_temp.v(3).y, color);
    LCD_DrawLine(p_temp.v(7).x, p_temp.v(7).y, 
                 p_temp.v(4).x, p_temp.v(4).y, color);
    LCD_DrawLine(p_temp.v(7).x, p_temp.v(7).y, 
                 p_temp.v(6).x, p_temp.v(6).y, color);
}

//Clear all the cubes using render_cubes(BLACK)
void render_cubes(unsigned short color){
    projected_cube temp;
    for(int i = 0; i < num_cubes; i++){
        render_cube(cubes[i], color);
    }
}
*/

void print_int(int i, char x, char y){
    LCD_Goto(x, y);
    out_int(i);
}
