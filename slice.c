/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:21:31 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/24 09:15:06 by aheinane         ###   ########.fr       */
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

void	drawing_ceil_floor(int px_y, int px_x, t_cub *data, t_wall *cur)
{
	if (px_y <= cur->start)
		mlx_put_pixel(data->image, px_x, px_y, data->texture.ceiling);
	if (px_y >= cur->end)
		mlx_put_pixel(data->image, px_x, px_y, data->texture.floor);
}

void	slice(t_cub *data, t_vector_i px)
{
	uint32_t	*pixels;

	pixels = (uint32_t *)data->ture.cur->pixels;
	if (px.y >= data->cur.start && px.y <= data->cur.end)
	{
		data->ture.tex.y = (int)(data->ture.start_tex) & \
			(data->ture.cur->height - 1);
		data->ture.start_tex += data->ture.step;
		data->ture.i = (int)(data->ture.tex.y * data->ture.cur->width + \
			data->ture.tex.x);
		if (data->ture.i < data->ture.cur->width * data->ture.cur->height)
			mlx_put_pixel(data->image, px.x, px.y, \
				norm_color(pixels[data->ture.i]));
	}
	drawing_ceil_floor(px.y, px.x, data, &data->cur);
}
