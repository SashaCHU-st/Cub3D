/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:21:21 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 09:29:21 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_player(t_textures *textures)
{
	printf("Wrong Player\n");
	error_fun(textures);
}

void	more_the_one_or_no(t_textures *textures)
{
	printf("No player or more then 1\n");
	error_fun(textures);
}

void	wrong_values_color(int j, char **colors, t_textures *text)
{
	free_color(j, colors);
	printf("Wrong values\n");
	error_fun(text);
}

void	malloc_fails(t_textures *textures)
{
	printf("Malloc fails\n");
	error_fun(textures);
}

void	error_map_not_closed(t_textures *textures)
{
	printf("Map is not closed\n");
	error_fun(textures);
}
