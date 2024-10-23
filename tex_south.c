/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_south.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:09 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 20:30:13 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_south_path(char *temp_so, t_textures *textures, int fd)
{
	if (ft_strncmp(temp_so, "textures/", 9) == 0)
		textures->so = temp_so;
	else
	{
		free(temp_so);
		closing(textures, fd, "Wrong path\n");
	}
}

void	checking_perm_for_south(char *temp_so, t_textures *textures,
		int j, int fd)
{
	if (textures->permission > 0)
	{
		if (check_if_png(temp_so))
		{
			while (temp_so[j] != '\0')
			{
				if (check_space(temp_so[j]))
				{
					free(temp_so);
					closing(textures, fd, "Wrong textures element\n");
					return ;
				}
				j++;
			}
			checking_south_path(temp_so, textures, fd);
		}
		close(textures->permission);
	}
	else
	{
		free(temp_so);
		closing(textures, fd, "No permission\n");
	}
}

void	so(t_textures *textures, char *line, int fd)
{
	int		i;
	int		j;
	char	*temp_so;

	i = 0;
	j = 0;
	if (ft_strncmp(&line[i], "SO", 2) == 0 && check_space(line[i + 2]))
	{
		textures->found_so += 1;
		if (textures->found_so > 1)
			closing(textures, fd, "More than one same element found\n");
		i += 2;
		temp_so = ft_strdup(avoid_whitespace(line + i));
		if (!temp_so)
		{
			closing(textures, fd, "Strdup error/ malloc\n");
			return ;
		}
		textures->permission = open(temp_so, O_RDONLY);
		checking_perm_for_south(temp_so, textures, j, fd);
	}
}
