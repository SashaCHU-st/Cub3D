/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:27:42 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/21 19:35:41 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_rgba(int r, int g, int b)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | \
		((uint32_t)b << 8) | 255);
}

int	check_coord(int x, int y, t_cub *data)
{
	if (data->texture.map[y][x] == '1')
		return (1);
	else
		return (0);
}	

void	set_wall_dist(t_wall *wall, t_cub *data, double step)
{
	if (wall->side == 'h')
	{
		if (wall->ray_dir.x == 0)
			wall->distance = (wall->map.x - data->texture.play.x \
				+ (1 - step) / 2) / EPSILON;
		else
			wall->distance = (wall->map.x - data->texture.play.x \
				+ (1 - step) / 2) / wall->ray_dir.x;
		wall->hit = data->texture.play.y + wall->distance * wall->ray_dir.y;
	}
	else
	{
		if (wall->ray_dir.y == 0)
			wall->distance = (wall->map.y - data->texture.play.y \
				+ (1 - step) / 2) / EPSILON;
		else
			wall->distance = (wall->map.y - data->texture.play.y \
				+ (1 - step) / 2) / wall->ray_dir.y;
		wall->hit = data->texture.play.x + wall->distance * wall->ray_dir.x;
	}
}
