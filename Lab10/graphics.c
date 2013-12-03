#include "graphics_tm4c123.h"
#include "game.h"
#include "LCD.h"

#define WIDTH 320 
#define HEIGHT 240
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800

#define clear_cubes() render_cubes(0)
#define v(a) vertices[a]
#define swap(a, b) do{int i = a; a = b; b = i;} while(0)

void print_int(int, char, char);

void render_cubes(unsigned short, unsigned short);
void render_cube_wireframe(projected_cube, unsigned short);
void render_cubes(unsigned short, unsigned short);

void render_cube_wireframe(projected_cube projection, unsigned short color){
    LCD_DrawLine(projection.v(0).x, projection.v(0).y, 
                 projection.v(1).x, projection.v(1).y, color);
    LCD_DrawLine(projection.v(0).x, projection.v(0).y, 
                 projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(0).x, projection.v(0).y, 
                 projection.v(4).x, projection.v(4).y, color);

    LCD_DrawLine(projection.v(2).x, projection.v(2).y, 
                 projection.v(1).x, projection.v(1).y, color);
    LCD_DrawLine(projection.v(2).x, projection.v(2).y, 
                 projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(2).x, projection.v(2).y, 
                 projection.v(6).x, projection.v(6).y, color);
   
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, 
                 projection.v(1).x, projection.v(1).y, color);
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, 
                 projection.v(4).x, projection.v(4).y, color);
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, 
                 projection.v(6).x, projection.v(6).y, color);
   
    LCD_DrawLine(projection.v(7).x, projection.v(7).y, 
                 projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(7).x, projection.v(7).y,
                 projection.v(4).x, projection.v(4).y, color);
    LCD_DrawLine(projection.v(7).x, projection.v(7).y, 
                 projection.v(6).x, projection.v(6).y, color);
}

void render_cube_fill(projected_cube projection, unsigned short color){
    int x, y;
    //Fill front face
    LCD_DrawFilledRect(projection.v(7).x, projection.v(7).y,
                       projection.v(2).x-projection.v(7).x,
                       projection.v(2).y-projection.v(7).y, color);
    //Fill top face and side face
    LCD_DrawFilledRect(projection.v(4).x, projection.v(4).y,
                       ((projection.v(5).x<projection.v(6).x)?
                        projection.v(5).x:projection.v(6).x)-projection.v(4).x,
                       projection.v(7).y-projection.v(4).y, BURNTORANGE);
    //If the cube is on the left or middle
    if (projection.v(7).x < projection.v(4).x) {
        //Lefty top triangle
        for (x=projection.v(7).x; x < projection.v(4).x; ++x){
            for (y=projection.v(4).y; y < projection.v(7).y; ++y){
                //if ((projection.v(4).x-projection.v(7).x)*y <
                //    (projection.v(7).y-projection.v(4).y)*x) {
                    LCD_DrawPixel(x, y, BLUE);
                //}
            }
        }
        if (projection.v(6).x < projection.v(5).x) {
            //Draw right face
            LCD_DrawFilledRect(projection.v(6).x, projection.v(6).y,
                               projection.v(2).x-projection.v(6).x,
                               projection.v(2).y-projection.v(6).y, BURNTORANGE);
            //Upper right triangle
            for (x=projection.v(6).x; x < projection.v(5).x; ++x){
                for (y=projection.v(5).y; y < projection.v(6).y; ++y){
                    if ((projection.v(5).x-projection.v(6).x)*y <
                        (projection.v(6).y-projection.v(5).y)*x) {
                        LCD_DrawPixel(x, y, BLUE);
                    }
                }
            }
            //Lower right triangle
            for (x=projection.v(2).x; x < projection.v(1).x; ++x){
                for (y=projection.v(1).y; y < projection.v(2).y; ++y){
                    if ((projection.v(1).x-projection.v(2).x)*y <
                        (projection.v(2).y-projection.v(1).y)*x) {
                        LCD_DrawPixel(x, y, BLUE);
                    }
                }
            }
        }
    }
    //If the cube is on the right or middle
    if (projection.v(5).x < projection.v(6).x) {
        //Righty top triangle
        for (x=projection.v(5).x; x < projection.v(6).x; ++x){
            for (y=projection.v(5).y; y < projection.v(6).y; ++y){
                if ((projection.v(6).x-projection.v(5).x)*y <
                    (projection.v(6).y-projection.v(5).y)*x) {
                    LCD_DrawPixel(x, y, ORANGE);
                }
            }
        }
        if (projection.v(4).x < projection.v(7).x) {
            //Draw left face
            LCD_DrawFilledRect(projection.v(4).x, projection.v(7).y,
                               projection.v(7).x-projection.v(4).x,
                               projection.v(3).y-projection.v(7).y, color);
            //Upper left triangle
            for (x=projection.v(5).x; x < projection.v(7).x; ++x){
                for (y=projection.v(5).y; y < projection.v(7).y; ++y){
                    if ((projection.v(7).x-projection.v(5).x)*y <
                        (projection.v(7).y-projection.v(5).y)*x) {
                        LCD_DrawPixel(x, y, YELLOW);
                    }
                }
            }
            //Lower left triangle
            for (x=projection.v(0).x; x < projection.v(3).x; ++x){
                for (y=projection.v(0).y; y < projection.v(3).y; ++y){
                    if ((projection.v(3).x-projection.v(0).x)*y <
                        (projection.v(3).y-projection.v(0).y)*x) {
                        LCD_DrawPixel(x, y, YELLOW);
                    }
                }
            }
        }
    }
}

//Clear all the cubes using render_cubes(BLACK)
void render_cubes(unsigned short outline, unsigned short fill){
    projected_cube projection;
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 8; j++){
            projection.v(j) = project(cubes[i].v(j));
        }
        render_cube_fill(projection, fill);
        render_cube_wireframe(projection, outline);
    }
}

void draw_player(){
    LCD_DrawLine(152, 231, 166, 231, 0);
    LCD_DrawLine(152, 231, 159, 224, 0);
    LCD_DrawLine(166, 231, 159, 224, 0);
}

void print_int(int i, char x, char y){
    LCD_Goto(x, y);
    out_int(i);
}
