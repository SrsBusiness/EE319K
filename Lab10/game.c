#include "game.h"
#include "LCD.h"
cube cubes[MAX_CUBES];
unsigned char num_cubes = 0;
char dx = 0;
char dy = 1;
unsigned char speed = 1;// 1 - 10

point focal_point = {159, MIN_INT, -119};

point player[64] = {{152, 0, -239}, {166, 0, -239}, {159, 3, -239}};
// projects point onto projection plane through focal point

pixel project(point cube){ 
    point temp = vector(focal_point, cube);
    /*
    out_int(temp.x);
    LCD_OutChar('\n');
    out_int(temp.y);
    LCD_OutChar('\n');
    out_int(temp.z);
    LCD_OutChar('\n');
    */
    return (pixel){(short)(temp.x * 200 / temp.y + 159), 
        (short)(temp.z * 200 / temp.y * -1 + 119)};
}


// calculates vector between 2 points
point vector(point start, point end){
    return (point){end.x - start.x, end.y - start.y, end.z - start.z};
}

// adds cube to game, returns -1 if overflow, otherwise returns
// updated # of cubes
int add_cube(cube cube){
    if(num_cubes == MAX_CUBES)
        return -1;
    cubes[num_cubes++] = cube;
    return num_cubes;
}

// removes cube from game, returns -1 if nothing removed,
// otherwise returns updated # of cubes
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
// boolean comparison operation on cubes
int equals(point cube1, point cube2){
    return cube1.x == cube2.x && cube1.y == cube2.y && cube1.z == cube2.z; 
}

//3D of player: (focal_point.x, focal_point.y + 15, focal_point.z - 159)
int collision(){
    return 0;         
}
