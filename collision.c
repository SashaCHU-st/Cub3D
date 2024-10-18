/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:28:46 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/18 12:52:47 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*init the hori variable for finding intersections across 
the horizontal grid lines;
calculate how much you need to iterate by to get from one x/y
to the next one across the horizontal grid*/
void	set_hori(t_cub *data, t_collision *cur, t_wall *wall)
{	
	if (wall->ray_dir.x == 0)
		cur->iterate.x = 1e30;
	else
		cur->iterate.x = fabs(1 / wall->ray_dir.x);
	if (wall->ray_dir.x < 0)
	{
		cur->hori.step = -1;
		cur->hori.dot = (data->texture.play.x - wall->map.x) * cur->iterate.x;
	}
	else
	{
		cur->hori.step = 1;
		cur->hori.dot = (-data->texture.play.x + wall->map.x + 1) \
			* cur->iterate.x;
	}
}

/*init the vert variable for finding intersections across 
the vertical grid lines;
check if the direction ray is 0 and if yes, change it;
if not, get the first next coordinate of intersection*/
void	set_vert(t_cub *data, t_collision *cur, t_wall *wall)
{
	if (wall->ray_dir.y == 0)
		cur->iterate.y = 1e30;
	else
		cur->iterate.y = fabs(1 / wall->ray_dir.y);
	if (wall->ray_dir.y < 0)
	{
		cur->vert.step = -1;
		cur->vert.dot = (data->texture.play.y - wall->map.y) * cur->iterate.y;
	}
	else
	{
		cur->vert.step = 1;
		cur->vert.dot = (-data->texture.play.y + wall->map.y + 1) \
			* cur->iterate.y;
	}
}

/*using DDA find the first intersection and across which grid line it is*/
void	do_dda(t_cub *data, t_collision *cur, t_wall *wall)
{
	while (!(check_coord((int)wall->map.x, (int)wall->map.y, data)))
	{
		if (cur->hori.dot < cur->vert.dot)
		{
			cur->hori.dot += cur->iterate.x;
			wall->map.x += cur->hori.step;
			wall->side = 'h';
		}
		else
		{
			cur->vert.dot += cur->iterate.y;
			wall->map.y += cur->vert.step;
			wall->side = 'v';
		}
	}
}

/*get the current angle of the ray using the player's current angle 
of direction and 30 (field of view / 2) and screen width and cur_pixel_x;
setting the wall variables values and adjusting the FOV for the 
fishbowl effect;
the angle ranges from -1 to 1*/
double	set_wall_angle(t_cub *data, t_wall *wall, int i)
{
	double	adjust_angle;
	double	angle;

	adjust_angle = 2 * (double)i / (double)WIDTH - 1;
	angle = (data->texture.play.angle + (30 * CONVERT) \
		* adjust_angle) * CONVERT;
	wall->map.x = (int)data->texture.play.x;
	wall->map.y = (int)data->texture.play.y;
	wall->dir.x = cos(angle);
	wall->dir.y = sin(angle);
	wall->camera.x = -(wall->dir.y) * PLANE;
	wall->camera.y = wall->dir.x * PLANE;
	wall->ray_dir.x = wall->dir.x + wall->camera.x * adjust_angle;
	wall->ray_dir.y = wall->dir.y + wall->camera.y * adjust_angle;
	return (angle);
}

double	get_collision(t_cub *data, t_wall *wall, int px_x)
{
	t_collision	cur;
	double		angle;

	cur.vert = (t_intersection){0};
	cur.hori = (t_intersection){0};
	angle = set_wall_angle(data, wall, px_x);
	set_hori(data, &cur, wall);
	set_vert(data, &cur, wall);
	do_dda(data, &cur, wall);
	if (wall->side == 'h')
	{
		if (wall->ray_dir.x == 0)
			wall->distance = (wall->map.x - data->texture.play.x + (1 - cur.hori.step) / 2) / EPSILON;
		else
			wall->distance = (wall->map.x - data->texture.play.x + (1 - cur.hori.step) / 2) / wall->ray_dir.x;
		wall->hit = data->texture.play.y + wall->distance * wall->ray_dir.y; //y coordinate where the wall was hit
	}
	else
	{
		if (wall->ray_dir.y == 0)
			wall->distance = (wall->map.y - data->texture.play.y + (1 - cur.vert.step) / 2) / EPSILON;
		else
			wall->distance = (wall->map.y - data->texture.play.y + (1 - cur.vert.step) / 2) / wall->ray_dir.y;
		wall->hit = data->texture.play.x + wall->distance * wall->ray_dir.x; //x coordinate where the wall was hit
	}
	//printf("found distance at %f\n", wall->distance);
	if (wall->hit < 0 || wall->hit > 1) //to ensure x is between 0 and 1; normalizing
		wall->hit -= floor(wall->hit);
	// printf("hit is %f\n", wall->hit);
	return (angle);
}
