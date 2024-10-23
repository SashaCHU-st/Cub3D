/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_east.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:55 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 15:36:10 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_east_path(char *temp_ea, t_textures *textures, int fd)
{
	if (ft_strncmp(temp_ea, "textures/", 9) == 0)
		textures->ea = temp_ea;
	else
	{
		free(temp_ea);
		closing(textures, fd, "Wrong path\n");
	}
}

void	checking_perm_for_east(char *temp_ea, t_textures *textures,
		int j, int fd)
{
	if (textures->permission > 0)
	{
		if (check_if_png(temp_ea))
		{
			while (temp_ea[j] != '\0')
			{
				if (check_space(temp_ea[j]))
				{
					free(temp_ea);
					closing(textures, fd, "Wrong textures element\n");
					return ;
				}
				j++;
			}
			checking_east_path(temp_ea, textures, fd);
		}
		close(textures->permission);
	}
	else
	{
		free(temp_ea);
		closing(textures, fd, "No permission\n");
	}
}

void	ea(t_textures *textures, char *line, int fd)
{
	int		i;
	int		j;
	char	*temp_ea;

	i = 0;
	j = 0;
	if (ft_strncmp(&line[i], "EA", 2) == 0 && check_space(line[i + 2]))
	{
		textures->found_ea += 1;
		if (textures->found_ea > 1)
			closing(textures, fd, "More than one same texture found\n");
		i += 2;
		temp_ea = ft_strdup(avoid_whitespace(line + i));
		if (!temp_ea)
		{
			closing(textures, fd, "Strdup error/ malloc\n");
			return ;
		}
		textures->permission = open(temp_ea, O_RDONLY);
		checking_perm_for_east(temp_ea, textures, j, fd);
	}
}
