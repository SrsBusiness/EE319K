#define MAX_CUBES 100

#define CUBE_SIZE 40
#define FOCAL_LENGTH 200
#define MIN_INT -2147483648

#define v(a) vertices[a]

// points for 3D-plane
struct point{
    int x, y, z;
} typedef point;

struct pixel{
    short x, y;
} typedef pixel;

struct cube{
    point vertices[8];
    unsigned short color;
} typedef cube;

struct projected_cube{
    pixel vertices[8];
} typedef projected_cube;

extern cube cubes[]; // array of cube vertices
extern unsigned char num_cubes;

// projection plane is plane where y = focal_point.y + FOCAL_LENGTH
// z is important for rendering, but not useful for the purpose of
// gameplay
extern point focal_point;

extern char dx, dy;
extern unsigned char speed;
// projects the cube onto the projection plane through the focal point



void vector(point start, point end, point *);

int collision();

int add_cube(cube);
void clean_cubes();

void new_cube(point, unsigned short, cube *);
//int equals(cube, cube);
