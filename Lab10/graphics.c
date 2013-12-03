#include "graphics_tm4c123.h"
#include "game.h"
#include "LCD.h"

#define WIDTH 320 
#define HEIGHT 240
#define swap(a, b) do{int i = a; a = b; b = i;} while(0)
void print_int(int, char, char);
/*
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
*/
void print_int(int i, char x, char y){
    LCD_Goto(x, y);
    out_int(i);
}
