#include "game.h"
#include "LCD.h"

#define MAX_Z 9001
#define CENTER_X 150

cube cubes[MAX_CUBES];
unsigned char num_cubes = 0;
char dx = 0;
char dy = 1;
unsigned char speed = 1;// 1 - 10

point focal_point = {159, MIN_INT, -119};

point player[3] = {{152, 15, -239}, {166, 15, -239}, {159, 30, -239}};

// Calculate vector between 2 points
void vector(point start, point end, point *vector){
    vector -> x = end.x - start.x;
    vector -> y = end.y - start.y;
    vector -> z = end.z - start.z;
}

// Adds cube to game.
//  If overflow: return -1.
//  Otherwise: return number of cubes in the world currently.
// Note: Uses painter's algorithm to order cubes so rendering is simple.
int add_cube(cube c){
    int i = 0, dist;
    cube temp_cube;
    //Calculate given cube's dist from center.
    int c_dist = c.v(0).x - CENTER_X;
    if (c_dist < 0) { c_dist *= -1; }
    //Cube limit
    if(num_cubes == MAX_CUBES) { return -1; }

    //Find correct spot for cube
    while(i < num_cubes) {
        //If c is less forward, move on.
        if (cubes[i].v(0).z < c.v(0).z){
            i++;
        } else {
            //Calculate distance from center
            dist = cubes[i].v(0).x - CENTER_X; if (dist < 0) { dist *= -1; }
            //If c is more centered and c.z == cubes[i].z, move on.
            if ((cubes[i].v(0).z == c.v(0).z) &&
                (c_dist > dist)) {
                i++;
            } else {
                break;
            }
        }
    }
    //Rotate to make a spot for the cube
    for(int j = num_cubes-1; j > i; --j){
        cubes[j] = cubes[j-1];
    }
    //Insert cube
    cubes[i] = c;
    //Update cube count
    return ++num_cubes;
}

// Removes cube from game.
//  If underflow: return -1.
//  Otherwise: return number of cubes in the world currently.
/*
int remove_cube(cube cube){
    for(int i = 0; i < num_cubes; i++){
        if(equals(cube, cubes[i])){
            for(int j = i + 1; j < num_cubes; j++){
                cubes[j - 1] = cubes[j];
            }
            return --num_cubes;
        }
    }
    return -1;
}
*/

// Cleans cubes with z value > MAX_Z from game.
void clean_cubes(){
    int i = 0, j = 0;
    int n = num_cubes;
    while(i < n){
        if (cubes[i].vertices[2].z > MAX_Z){
            num_cubes--;
        } else {
            cubes[j++] = cubes[i];
        }
        i++;
    }
}

// boolean comparison operation on cubes
int equals(point cube1, point cube2){
    return cube1.x == cube2.x && cube1.y == cube2.y && cube1.z == cube2.z; 
}

//3D of player: (focal_point.x, focal_point.y + 15, focal_point.z - 159)
//point player[3] = {{focal_point.x - 7, 200 + focal_point.y, -239}, 
//{focal_point.x + 7, 200 + focal_point.y, -239}, 
//{focal_point.x, 203 + focal_point.y, -239}};
int collision(){
    for(int i = 0; i < num_cubes; i++){
        for(int j = 0; j < 4; j++){
            // positive slope
            int b0 = focal_point.y + 200 - 5 * (focal_point.x + 7);
            // negative slope
            int b1 = focal_point.y + 200 + 5 * (focal_point.x + 7);
            if(cubes[i].vertices[j].x * 5 + b0 >= cubes[i].vertices[j].y &&
                    cubes[i].vertices[j].x * -5 + b1 >= cubes[i].vertices[j].y)
                return 1;
        }
    }
    return 0;
}

void new_cube(point base, unsigned short color, cube *new){
    *new = (cube){{{base.x, base.y, base.z}, 
        {base.x + CUBE_SIZE, base.y, base.z},
        {base.x + CUBE_SIZE, base.y - CUBE_SIZE, base.z},
        {base.x, base.y - CUBE_SIZE, base.z},
        {base.x, base.y, base.z + CUBE_SIZE},
        {base.x + CUBE_SIZE, base.y, base.z + CUBE_SIZE},
        {base.x + CUBE_SIZE, base.y - CUBE_SIZE, base.z + CUBE_SIZE},
        {base.x, base.y - CUBE_SIZE, base.z + CUBE_SIZE}}, color};
}
