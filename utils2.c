/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:27:42 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/18 10:38:41 by aheinane         ###   ########.fr       */
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
