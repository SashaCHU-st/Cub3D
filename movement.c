/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:39:41 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/14 15:39:52 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	ft_move_up(t_cub *data)
{
	t_vector	angle;

	angle.x = cos(data->texture.play.angle * CONVERT);
	angle.y = sin(data->texture.play.angle * CONVERT);
	if (check_coord((int)(data->texture.play.x + (0.5 * angle.x)), (int)(data->texture.play.y + (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x += 0.5 * angle.x;
		data->texture.play.y += 0.5 * angle.y;
	}
}

void	ft_move_down(t_cub *data)
{
	t_vector	angle;

	angle.x = cos(data->texture.play.angle * CONVERT);
	angle.y = sin(data->texture.play.angle * CONVERT);
	if (check_coord((int)(data->texture.play.x - (0.5 * angle.x)), (int)(data->texture.play.y - (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x -= 0.5 * angle.x;
		data->texture.play.y -= 0.5 * angle.y;
	}
}

void	ft_move_left(t_cub *data)
{
	t_vector	angle;

	angle.x = sin(data->texture.play.angle * CONVERT);
	angle.y = cos(data->texture.play.angle * CONVERT);
	if (check_coord((int)(data->texture.play.x + (0.5 * angle.x)), \
	(int)(data->texture.play.y + (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x += 0.5 * angle.x;
		data->texture.play.y += 0.5 * angle.y;
	}
}

void	ft_move_right(t_cub *data)
{
	t_vector	angle;

	angle.x = sin(data->texture.play.angle * CONVERT);
	angle.y = cos(data->texture.play.angle * CONVERT);
	if (check_coord((int)(data->texture.play.x - (0.5 * angle.x)), \
	(int)(data->texture.play.y - (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x -= 0.5 * angle.x;
		data->texture.play.y -= 0.5 * angle.y;
	}
}