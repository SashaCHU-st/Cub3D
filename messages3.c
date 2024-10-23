/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:43:26 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 12:45:48 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_out_of_range(int *values, int i, t_textures *text, int fd)
{
	if (values[i] > 255 || values[i] < 0)
	{
		printf("Values must be from 0 to 255\n");
		closing(text, fd);
	}
}
