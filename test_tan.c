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
    int x;
    int y;
} t_coll;
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
    printf("result is %f\n", b);

    //to iterate: i++, c + 30 / WIDTH;

    printf("the res is %d\n", 224 / 64);

    int grid_x = 1;
    int grid_y = 3;
    int Px = grid_x * 64 + 32; //or 3.5 in grid coordinates
    int Py = grid_y * 64 + 32; //or 1.5
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
    while(!check_coord(vert->x / 64, vert->y / 64, map))
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
    while(!check_coord(hori->x / 64, hori->y / 64, map))
    {
        hori->x = hori->x + hori->h;
        hori->y = hori->y + hori->v;
    }
    save_coord(hori->x, hori->y, ision_h);
*/

}

/*
int   check_coord(int x, int y, t_map **map)
{
    return (map[y][x]);
}

void    save_coord(int x, int y, t_coll ision)
{
    ision->x = x;
    ision->y = y;
}
*/
