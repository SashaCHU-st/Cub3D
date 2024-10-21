/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:34:14 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/21 17:46:02 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*get_wall_color(t_wall *cur, double angle, t_cub *data)
{
	if (cur->side == 'v')
	{
		if (angle > 0 * CONVERT && angle < 180 * CONVERT)
			return (data->texture.no_side);
		else
			return (data->texture.so_side);
	}
	if (cur->side == 'h')
	{
		if (angle > 90 * CONVERT && angle < 270 * CONVERT)
			return (data->texture.we_side);
		else
			return (data->texture.ea_side);
	}
	return (NULL);
}

/*for getting the exact x coordinate of the texture with a check
to see if x needs to be corrected based on ray direction and
wall orientation*/
double	get_tex_x(mlx_texture_t *from_texture, t_wall *cur)
{
	int	x;

	x = (int)(cur->hit * (double)from_texture->width);
	if ((cur->side == 'v' && cur->ray_dir.y < 0) || \
		(cur->side == 'h' && cur->ray_dir.x > 0))
		x = from_texture->width - x - 1;
	return (x);
}

void	set_draw_tex(t_cub *data, double angle)
{
	data->ture.cur = get_wall_color(&data->cur, angle, data);
	data->ture.tex.x = get_tex_x(data->ture.cur, &data->cur);
	data->ture.step = ((double)data->ture.cur->height / data->cur.height);
	data->ture.start_tex = (data->cur.start - HEIGHT / 2 + \
		data->cur.height / 2) * data->ture.step;
	data->ture.tex.y = (int)(data->ture.start_tex) & \
		(data->ture.cur->height - 1);
}

void	calc_wall(t_wall *cur)
{
	if (cur->distance == 0)
		cur->distance = EPSILON;
	cur->height = fabs((HEIGHT / cur->distance));
	cur->start = fabs(HEIGHT / 2 - cur->height / 2);
	cur->end = fabs(HEIGHT / 2 + cur->height / 2);
	if (cur->height == 0)
		cur->height = EPSILON;
}

void	ft_draw_window(void *param)
{
	t_cub		*data;
	double		angle;
	t_vector_i	px;

	px.x = 0;
	data = (t_cub *)param;
	while (px.x < WIDTH)
	{
		angle = get_collision(data, &data->cur, px.x);
		calc_wall(&data->cur);
		set_draw_tex(data, angle);
		px.y = 0;
		while (px.y < HEIGHT)
		{
			slice(data, px);
			px.y++;
		}
		px.x++;
	}
}
