/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 10:50:14 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_textures(t_textures *textures, char *line, int fd)
{
	no(textures, line, fd);
	so(textures, line, fd);
	we(textures, line, fd);
	ea(textures, line, fd);
}
