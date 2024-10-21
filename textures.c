/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 13:48:56 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_textures(t_textures *textures, char *line)
{
	no(textures, line);
	so(textures, line);
	we(textures, line);
	ea(textures, line);
}
