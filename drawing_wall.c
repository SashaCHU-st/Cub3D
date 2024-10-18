/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:33:11 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/18 17:33:23 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	norm_color(int c)
{
	unsigned char	bytes[4];
	int				reversed;
	unsigned char	reversed_bytes[4];

	ft_memcpy(bytes, &c, sizeof(int));
	reversed_bytes[0] = bytes[3];
	reversed_bytes[1] = bytes[2];
	reversed_bytes[2] = bytes[1];
	reversed_bytes[3] = bytes[0];
	ft_memcpy(&reversed, reversed_bytes, sizeof(int));
	return (reversed);
}

void drawing_ceil_floor(int px_y, int px_x, t_cub *data, t_wall cur )
{
	if(px_y <=cur.start)
		mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
	if(px_y >= cur.end)
		mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
}

mlx_texture_t *get_wall_color(t_wall cur, double angle, t_cub *data)
{
	if(cur.side == 'v')
	{
		if(angle > 0*CONVERT && angle < 180 *CONVERT)
			return(data->texture.no_side);
		else
			return(data->texture.so_side);
		
	}
	if(cur.side == 'h')
	{
		if(angle > 90*CONVERT && angle < 270 *CONVERT)
			return(data->texture.we_side);
		else
			return(data->texture.ea_side);
	}
	return (NULL);
}