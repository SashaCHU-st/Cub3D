/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:21:21 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 14:58:17 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_values_color(int j, char **colors, t_textures *text, int fd)
{
	free_color(j, colors);
	closing(text, fd, "Wrong values\n");
}

void	failed_to_copy(t_textures *textures, int fd)
{
	free(textures->line);
	closing(textures, fd, "Malloc fails\n");
}

void	color_out_of_range(int *values, int i, t_textures *text, int fd)
{
	if (values[i] > 255 || values[i] < 0)
	{
		closing(text, fd, "Values must be from 0 to 255\n");
	}
}
