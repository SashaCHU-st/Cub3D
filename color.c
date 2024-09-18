/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:30 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/18 14:03:46 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	checking_color(t_textures *textures, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0 && &check_space)
	{
		textures->found_f = 1;
		textures->floor_color = ft_strdup(avoid_whitespace(line + 2 + 1));
		printf("FLOOR: \n %s\n", textures->floor_color);
	}
	else if (ft_strncmp(line, "C", 1) == 0 && &check_space)
	{
		textures->found_c = 1;
		textures->ceiling_color= ft_strdup(avoid_whitespace(line + 2 + 1));
		printf("CEILING: \n %s\n", textures->ceiling_color);
	}
}