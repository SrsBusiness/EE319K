#include "graphics_tm4c123.h"
#include "game.h"
#include "LCD.h"

#define WIDTH 320 
#define HEIGHT 240

#define v(a) vertices[a]
#define swap(a, b) do{int i = a; a = b; b = i;} while(0)

void print_int(int, char, char);

void render_cube_wireframe_alpha(projected_cube projection, unsigned short color){
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

void render_cube_wireframe(projected_cube projection, unsigned short color){
    //Front
    LCD_DrawLine(projection.v(2).x, projection.v(2).y, 
                 projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(3).x, projection.v(3).y, 
                 projection.v(7).x, projection.v(7).y, color);
    LCD_DrawLine(projection.v(7).x, projection.v(7).y, 
                 projection.v(6).x, projection.v(6).y, color);
    LCD_DrawLine(projection.v(6).x, projection.v(6).y, 
                 projection.v(2).x, projection.v(2).y, color);
    //Top
    LCD_DrawLine(projection.v(6).x, projection.v(6).y, 
                 projection.v(5).x, projection.v(5).y, color);
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, 
                 projection.v(4).x, projection.v(4).y, color);
    LCD_DrawLine(projection.v(4).x, projection.v(4).y, 
                 projection.v(7).x, projection.v(7).y, color);
    //Cube on left side
    if (projection.v(6).x < projection.v(5).x) {
        LCD_DrawLine(projection.v(2).x, projection.v(2).y, 
                     projection.v(1).x, projection.v(1).y, color);
        LCD_DrawLine(projection.v(1).x, projection.v(1).y, 
                     projection.v(5).x, projection.v(5).y, color);
    //Cube on right side
    } else if (projection.v(4).x < projection.v(7).x) {
        LCD_DrawLine(projection.v(3).x, projection.v(3).y, 
                     projection.v(0).x, projection.v(0).y, color);
        LCD_DrawLine(projection.v(0).x, projection.v(0).y, 
                     projection.v(4).x, projection.v(4).y, color);
    }
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
                       projection.v(7).y-projection.v(4).y, GREEN);
    //Cube on left side
    if (projection.v(6).x < projection.v(5).x) {
        //Lefty top triangle
        for (x=projection.v(7).x; x < projection.v(4).x; ++x){
            for (y=projection.v(4).y; y < projection.v(7).y; ++y){
                if (((projection.v(4).x-projection.v(7).x)*(y-projection.v(4).y)) <=
                    ((projection.v(7).y-projection.v(4).y)*(x-projection.v(7).x))) {
                    LCD_DrawPixel(x, projection.v(7).y-(y-projection.v(4).y), GREEN);
                }
            }
        }
        //Righty top triangle
        for (x=projection.v(6).x; x < projection.v(5).x; ++x){
            for (y=projection.v(5).y; y < projection.v(6).y; ++y){
                if ((projection.v(5).x-projection.v(6).x)*(y-projection.v(5).y) <=
                    (projection.v(6).y-projection.v(5).y)*(x-projection.v(6).x)) {
                    LCD_DrawPixel(x, projection.v(6).y-(y-projection.v(5).y), BLUE);
                } else {
                    LCD_DrawPixel(x, projection.v(6).y-(y-projection.v(5).y), GREEN);
                }
            }
        }
        //Draw right face
        LCD_DrawFilledRect(projection.v(6).x, projection.v(6).y,
                           projection.v(1).x-projection.v(6).x,
                           projection.v(1).y-projection.v(6).y + 1, BLUE);
        //Lower right triangle
        for (x=projection.v(2).x; x < projection.v(1).x; ++x){
            for (y=projection.v(1).y; y < projection.v(2).y; ++y){
                if ((projection.v(1).x-projection.v(2).x)*(y-projection.v(1).y) >=
                    (projection.v(2).y-projection.v(1).y)*(x-projection.v(2).x)) {
                    LCD_DrawPixel(x, projection.v(2).y-(y-projection.v(1).y), BLUE);
                }
            }
        }
    //Cube on right side
    } else if (projection.v(4).x < projection.v(7).x) {
        //Lefty top triangle
        for (x=projection.v(4).x; x < projection.v(7).x; ++x){
            for (y=projection.v(4).y; y < projection.v(7).y; ++y){
                if ((projection.v(7).x-projection.v(4).x)*(y-projection.v(4).y) <=
                    (projection.v(7).y-projection.v(4).y)*(x-projection.v(4).x)) {
                    LCD_DrawPixel(x, y, GREEN);
                } else {
                    LCD_DrawPixel(x, y, YELLOW);
                }
            }
        }
        //Righty top triangle
        for (x=projection.v(5).x; x < projection.v(6).x; ++x){
            for (y=projection.v(5).y; y < projection.v(6).y; ++y){
                if ((projection.v(6).x-projection.v(5).x)*(y-projection.v(5).y) >=
                    (projection.v(6).y-projection.v(5).y)*(x-projection.v(5).x)) {
                    LCD_DrawPixel(x, y, GREEN);
                }
            }
        }
        //Draw left face
        LCD_DrawFilledRect(projection.v(4).x, projection.v(7).y,
                           projection.v(7).x-projection.v(4).x,
                           projection.v(0).y-projection.v(7).y, YELLOW);
        //Lower left triangle
        for (x=projection.v(0).x; x < projection.v(3).x; ++x){
            for (y=projection.v(0).y; y < projection.v(3).y; ++y){
                if ((projection.v(3).x-projection.v(0).x)*(y-projection.v(0).y) <=
                    (projection.v(3).y-projection.v(0).y)*(x-projection.v(0).x)) {
                    LCD_DrawPixel(x, y, YELLOW);
                }
            }
        }
    //Cube in middle
    } else {
        //Lefty top triangle
        for (x=projection.v(7).x; x < projection.v(4).x; ++x){
            for (y=projection.v(4).y; y < projection.v(7).y; ++y){
                if (((projection.v(4).x-projection.v(7).x)*(y-projection.v(4).y)) <=
                        ((projection.v(7).y-projection.v(4).y)*(x-projection.v(7).x))) {
                    LCD_DrawPixel(x, projection.v(7).y-(y-projection.v(4).y), GREEN);
                }
            }
        }
        //Righty top triangle
        for (x=projection.v(5).x; x < projection.v(6).x; ++x){
            for (y=projection.v(5).y; y < projection.v(6).y; ++y){
                if ((projection.v(6).x-projection.v(5).x)*(y-projection.v(5).y) <=
                        (projection.v(6).y-projection.v(5).y)*(x-projection.v(5).x)) {
                    LCD_DrawPixel(x, y, GREEN);
                }
            }
        }
    }
}

//Clear all the cubes using render_cubes(WHITE, WHITE)
void render_cubes(unsigned short outline, unsigned short fill){
    projected_cube projection;
    pixel temp;
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 8; j++){
            project(cubes[i].v(j), &temp);
            projection.v(j).x = temp.x;
            projection.v(j).y = temp.y;
        }
        render_cube_fill(projection, fill);
        render_cube_wireframe(projection, outline);
    }
}

//Projects point onto projection plane through focal point
void project(point cube, pixel *projection){
    point temp;
    vector(focal_point, cube, &temp);
    projection -> x = (short)(temp.x * 200 / temp.y + 159); 
    projection -> y = (short)(temp.z * 200 / temp.y * -1 + 119);
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

