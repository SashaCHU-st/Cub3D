/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_north.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:46:14 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 15:36:19 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_north_path(char *temp_no, t_textures *textures, int fd)
{
	if (ft_strncmp(temp_no, "textures/", 9) == 0)
		textures->no = temp_no;
	else
	{
		free(temp_no);
		closing(textures, fd, "Wrong path\n");
	}
}

void	checking_perm_for_north(char *temp_no, t_textures *textures,
		int j, int fd)
{
	if (textures->permission > 0)
	{
		if (check_if_png(temp_no))
		{
			while (temp_no[j] != '\0')
			{
				if (check_space(temp_no[j]))
				{
					free(temp_no);
					closing(textures, fd, "Wrong textures element\n");
					return ;
				}
				j++;
			}
			checking_north_path(temp_no, textures, fd);
		}
		close(textures->permission);
	}
	else
	{
		free(temp_no);
		closing(textures, fd, "No permission\n");
	}
}

void	no(t_textures *textures, char *line, int fd)
{
	int		i;
	int		j;
	char	*temp_no;

	j = 0;
	i = 0;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && check_space(line[i + 2]))
	{
		textures->found_no += 1;
		if (textures->found_no > 1)
			closing(textures, fd, "More than one same texture found\n");
		i += 2;
		temp_no = ft_strdup(avoid_whitespace(line + i));
		if (!temp_no)
		{
			closing(textures, fd, "Strdup error/ malloc\n");
			return ;
		}
		textures->permission = open(temp_no, O_RDONLY);
		checking_perm_for_north(temp_no, textures, j, fd);
	}
}
