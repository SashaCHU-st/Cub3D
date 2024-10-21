/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_and_hori.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:30:40 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 10:08:46 by aheinane         ###   ########.fr       */
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
