/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:21:55 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/23 12:57:40 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_up(t_cub *data)
{
	t_vector	angle;

	angle.x = cos(data->texture.play.angle * g_convert);
	angle.y = sin(data->texture.play.angle * g_convert);
	if (check_coord((int)(data->texture.play.x + (0.5 * angle.x)), \
		(int)(data->texture.play.y + (0.5 * angle.y)), data) == 0 && \
		data->cur.distance > 0.7)
	{
		data->texture.play.x += 0.5 * angle.x;
		data->texture.play.y += 0.5 * angle.y;
	}
}

void	ft_move_down(t_cub *data)
{
	t_vector	angle;

	angle.x = cos(data->texture.play.angle * g_convert);
	angle.y = sin(data->texture.play.angle * g_convert);
	if (check_coord((int)(data->texture.play.x - (0.5 * angle.x)), \
		(int)(data->texture.play.y - (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x -= 0.5 * angle.x;
		data->texture.play.y -= 0.5 * angle.y;
	}
}

void	ft_move_right(t_cub *data)
{
	t_vector	angle;

	angle.x = cos((data->texture.play.angle + 90) * g_convert);
	angle.y = sin((data->texture.play.angle + 90) * g_convert);
	if (check_coord((int)(data->texture.play.x + (0.5 * angle.x)), \
		(int)(data->texture.play.y + (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x += 0.5 * angle.x;
		data->texture.play.y += 0.5 * angle.y;
	}
}

void	ft_move_left(t_cub *data)
{
	t_vector	angle;

	angle.x = cos((data->texture.play.angle - 90) * g_convert);
	angle.y = sin((data->texture.play.angle - 90) * g_convert);
	if (check_coord((int)(data->texture.play.x + (0.5 * angle.x)), \
		(int)(data->texture.play.y + (0.5 * angle.y)), data) == 0)
	{
		data->texture.play.x += 0.5 * angle.x;
		data->texture.play.y += 0.5 * angle.y;
	}
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*data;

	data = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		ft_move_up(data);
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		ft_move_down(data);
	if (keydata.key == MLX_KEY_A)
		ft_move_left(data);
	if (keydata.key == MLX_KEY_D)
		ft_move_right(data);
	if (keydata.key == MLX_KEY_LEFT)
	{
		data->texture.play.angle -= 15;
		if (data->texture.play.angle < 0)
			data->texture.play.angle += 360;
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		data->texture.play.angle += 15;
		if (data->texture.play.angle >= 360)
			data->texture.play.angle -= 360;
	}
}
