#include "graphics_tm4c123.h"
#include "game.h"
#include "LCD.h"



#define swap(a, b) do{int i = a; a = b; b = i;} while(0)

char render = 0;

void print_int(int, char, char);
void project(point, pixel *);

void render_cube_wireframe_alpha(projected_cube projection, unsigned short color){
    LCD_DrawLine(projection.v(0).x, projection.v(0).y, projection.v(1).x, projection.v(1).y, color);
    LCD_DrawLine(projection.v(0).x, projection.v(0).y, projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(0).x, projection.v(0).y, projection.v(4).x, projection.v(4).y, color);
    
    LCD_DrawLine(projection.v(2).x, projection.v(2).y, projection.v(1).x, projection.v(1).y, color);
    LCD_DrawLine(projection.v(2).x, projection.v(2).y, projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(2).x, projection.v(2).y, projection.v(6).x, projection.v(6).y, color);
   
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, projection.v(1).x, projection.v(1).y, color);
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, projection.v(4).x, projection.v(4).y, color);
    LCD_DrawLine(projection.v(5).x, projection.v(5).y, projection.v(6).x, projection.v(6).y, color);
    
    LCD_DrawLine(projection.v(7).x, projection.v(7).y, projection.v(3).x, projection.v(3).y, color);
    LCD_DrawLine(projection.v(7).x, projection.v(7).y, projection.v(4).x, projection.v(4).y, color);
    LCD_DrawLine(projection.v(7).x, projection.v(7).y, projection.v(6).x, projection.v(6).y, color);
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
                if ((projection.v(4).x-projection.v(7).x)*(y-projection.v(4).y) <=
                    (projection.v(7).y-projection.v(4).y)*(x-projection.v(7).x)) {
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
                if ((projection.v(4).x-projection.v(7).x)*(y-projection.v(4).y) <=
                    (projection.v(7).y-projection.v(4).y)*(x-projection.v(7).x)) {
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

//Fill white in the 
void render_cube_reset(projected_cube projection) {
    //Fill top face and side face
    LCD_DrawFilledRect((projection.v(4).x < projection.v(7).x ?
                        projection.v(4).x : projection.v(7).x),
                        projection.v(4).y,
                       (projection.v(5).x > projection.v(6).x ?
                        projection.v(5).x : projection.v(6).x) -
                       (projection.v(4).x < projection.v(7).x ?
                        projection.v(4).x : projection.v(7).x),
                       2+projection.v(7).y-projection.v(4).y+2, WHITE);
    //Cube on left side
    if (projection.v(6).x < projection.v(5).x) {
        //Draw right face
        LCD_DrawFilledRect(projection.v(6).x-2, projection.v(5).y,
                           projection.v(1).x-projection.v(6).x,
                           projection.v(2).y-projection.v(5).y, WHITE);
    //Cube on right side
    } else if (projection.v(4).x < projection.v(7).x) {
        //Draw left face
        LCD_DrawFilledRect(projection.v(4).x, projection.v(4).y,
                           projection.v(3).x-projection.v(4).x+2,
                           projection.v(3).y-projection.v(4).y, WHITE);
    }
}

//Clear out the frame of the cube.
//Only neeeded for drawing filled cubes.
void clear_cube_frames(){
    projected_cube projection;
    pixel temp;
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 8; j++){
            project(cubes[i].v(j), &temp);
            projection.v(j).x = temp.x;
            projection.v(j).y = temp.y;
        }
        render_cube_reset(projection);
    }
}

void render_cubes(unsigned short outline, unsigned short fill){
    projected_cube projection;
    pixel temp;
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 8; j++){
            project(cubes[i].v(j), &temp);
            projection.v(j).x = temp.x;
            projection.v(j).y = temp.y;
        }
        // render_cube_fill(projection, fill);
        render_cube_wireframe_alpha(projection, outline);
    }
}

//Projects point onto projection plane through focal point
void project(point cube, pixel *projection){
    point temp;
    vector(focal_point, cube, &temp);
    projection -> x = (short)(temp.x * FOCAL_LENGTH / temp.y + 159); 
    projection -> y = (short)(temp.z * FOCAL_LENGTH / temp.y * -1 + 40);
}

//point player[3] = {{focal_point.x - 7, 200 + focal_point.y, -239}, 
//{focal_point.x + 7, 200 + focal_point.y, -239}, 
//{focal_point.x, 203 + focal_point.y, -239}};

void draw_player(){
	point p1 = {focal_point.x - 5, FOCAL_LENGTH + focal_point.y - 150, -239};
	point p2 = {focal_point.x + 5, FOCAL_LENGTH + focal_point.y - 150, -239};
	point p3 = {focal_point.x, 15 + FOCAL_LENGTH + focal_point.y - 150, -239};
	pixel pixel1, pixel2, pixel3;
	project(p1, &pixel1);
    project(p2, &pixel2);
	project(p3, &pixel3);
	LCD_DrawLine(pixel1.x, pixel1.y, pixel2.x, pixel2.y, GREEN);
    LCD_DrawLine(pixel1.x, pixel1.y, pixel3.x, pixel3.y, GREEN);
    LCD_DrawLine(pixel2.x, pixel2.y, pixel3.x, pixel3.y, GREEN);
}
/*
//Draws the player with a integer offset from the center.
void draw_player(int player_x){ 
    LCD_DrawLine(152+player_x, 231, 166+player_x, 231, 0); //base
    LCD_DrawLine(152+player_x, 231, 159+player_x, 224, 0);
    LCD_DrawLine(166+player_x, 231, 159+player_x, 224, 0);
}
 */

void print_int(int i, char x, char y){
    LCD_Goto(x, y);
    out_int(i);
}

