#include <math.h>
#include <stdio.h>
/*
typedef struct s_intersection
{
    int x;
    int y;
    int v;
    int h;
    int alpha; ?
}

typedef struct s_coll
{
    int     x;
    int     y;
    double  distance;
} t_coll;

int WIDTH = 512;
int HEIGHT = 512;
double D2R = tan(30 * M_PI / 180); 
int PROJ_PLANE_DIST = WIDTH / 2 / D2R;
//PROJ_SLICE_HEIGHT_CONST = 64 / PROJ_PLANE_DIST;
*/
int main(void)
{
    int WIDTH = 320;
    double  a;
    double  b;
    double  c;
    double  d_to_r;

    a = WIDTH / 2;
    d_to_r = 30 * M_PI /180;
    b = a / tan(d_to_r);
    c = sqrt(a * a + b * b);
    printf("result is %d\n", (int)b);

    //to iterate: i++, c + 30 / WIDTH;

    printf("the res is %d\n", 224 / 64);

    // int grid_x = 1;
    // int grid_y = 3;
    // int Px = grid_x * 64 + 32; //or 3.5 in grid coordinates
    // int Py = grid_y * 64 + 32; //or 1.5
    double proj_plane_dist = (512 / 2) / d_to_r;
    printf("check = %f\n", proj_plane_dist);
    //while grid coordinates don't indicate a wall
    //find the next ray-ed point
    //find the first intersection (grid) coordinates horizontally and vertically
    //save ray lengths?
/*
    have p_x, p_y, r_angle
    t_intersection hori;
    t_intersection vert;
    t_coll ision_v;
    t_coll ision_h;

//vertical intersections
    if (r_angle > 0 && < 180)
    {
        vert->y = ((int)p_y/64) * 64 - 1;
        vert->v = -64;
    }
    else if (r_angle > 180 < 360)
    {
        vert->y = ((int)p_y/64) * 64 + 64;
        vert->v = 64;
    }
    vert->x = p_x + (p_y - vert->y)/tan(alpha);
    vert->h = 64 / tan(alpha);
    while(!check_coord(vert->x, vert->y, map))
    {
        vert->x = vert->x + vert->h;
        vert->y = vert->y + vert->v;
    }
    save_coord(vert->x, vert->y, ision_v);

//horizontal intersections
    if (r_angle > 90 && < 270)
    {
        hori->x = ((int)p_x/64) * 64 + 64;
        hori->h = 64;
    }
    else if (r_angle > 270 < 360 || > 0 < 90)
    {
        hori->x = ((int)p_x/64) * 64 - 1;
        hori->h = -64;
    }
    hori->y = p_y - (hori->x - p->x)/tan(alpha);
    hori->v = 64 * tan(alpha);
    while(!check_coord(hori->x, hori->y, map))
    {
        hori->x = hori->x + hori->h;
        hori->y = hori->y + hori->v;
    }
    save_coord(hori->x, hori->y, ision_h);

    //somehow compare ision_h and ision_v and determine which one is shorter distance 
    to the wall maybe after this next step?
    //the guide says "The sine or cosine functions are cheaper to 
    implement because they can be pre-computed and put into tables."
    does this mean saving all the possible results for sin and cos
    in a double array or two separate arrays for each? considering the
    options range from 0 to 360
//since PD and PE can be caluclated in two different ways, maybe to lower the amount of
calculations we choose just one option per each? or does it need to be consistent?
vert->distance = abs(p_y - vert->y) / sin(alpha);
hori->distance = abs(p_x - hori->x) / cos(alpha);

//fishbowl effect
    dist_dist vs corr_dist
    corr_dist = cos(beta) * dist_dist;
    projected_wall_height = 64 / (PROJ_PLANE_DIST * corr_dist);
    //if this is equal 54 for example, the wall should be drawn as having the 
    length of 54 (/ 2, half drawn on the each side of the centre of the projecction plane
    ie HEIGHT / 2, so 27 units of the wall go above and 27 below the centre point)
*/

}

/*
int   check_coord(int x, int y, t_map **map)
{
    return (map[y / 64][x / 64]);
}

void    save_coord(int x, int y, t_coll ision)
{
    ision->x = x;
    ision->y = y;
}
*/
