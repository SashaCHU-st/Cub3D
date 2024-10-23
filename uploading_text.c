/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploading_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:40:19 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 09:42:09 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	uploading_text(t_textures *textures)
{
	textures->no_side = mlx_load_png(textures->no);
	if (!textures->no_side)
	{
		printf("cannot upload texture\n");
		error_fun(textures);
	}
	textures->so_side = mlx_load_png(textures->so);
	if (!textures->so_side)
	{
		printf("cannot upload texture\n");
		error_fun(textures);
	}
	textures->we_side = mlx_load_png(textures->we);
	if (!textures->we_side)
	{
		printf("cannot upload texture\n");
		error_fun(textures);
	}
	textures->ea_side = mlx_load_png(textures->ea);
	if (!textures->ea_side)
	{
		printf("cannot upload texture\n");
		error_fun(textures);
	}
}
