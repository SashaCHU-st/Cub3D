/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploading_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:40:19 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/24 12:30:22 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_text(mlx_texture_t *tex)
{
	if (tex->height == tex->width)
		return (1);
	return (0);
}

void	uploading_text(t_textures *textures, int fd)
{
	textures->no_side = mlx_load_png(textures->no);
	if (!textures->no_side || !check_text(textures->no_side))
		closing(textures, fd, "Cannot upload texture\n");
	textures->so_side = mlx_load_png(textures->so);
	if (!textures->so_side || !check_text(textures->so_side))
		closing(textures, fd, "Cannot upload texture\n");
	textures->we_side = mlx_load_png(textures->we);
	if (!textures->we_side || !check_text(textures->we_side))
		closing(textures, fd, "Cannot upload texture\n");
	textures->ea_side = mlx_load_png(textures->ea);
	if (!textures->ea_side || !check_text(textures->ea_side))
		closing(textures, fd, "Cannot upload texture\n");
}
