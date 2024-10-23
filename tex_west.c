/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_west.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:48:38 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 14:45:10 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_west_path(char *temp_we, t_textures *textures, int fd)
{
	if (ft_strncmp(temp_we, "textures/", 9) == 0)
	{
		textures->we = temp_we;
		textures->found_we += 1;
	}
	else
	{
		free(temp_we);
		closing(textures, fd, "Wrong path\n");
	}
}

void	checking_perm_for_west(char *temp_we, t_textures *textures,
		int j, int fd)
{
	if (textures->permission > 0)
	{
		if (check_if_png(temp_we))
		{
			while (temp_we[j] != '\0')
			{
				if (check_space(temp_we[j]))
				{
					free(temp_we);
					closing(textures, fd, "Wrong textures element\n");
					return ;
				}
				j++;
			}
			checking_west_path(temp_we, textures, fd);
		}
		close(textures->permission);
	}
	else
	{
		free(temp_we);
		closing(textures, fd, "No permission\n");
	}
}

void	we(t_textures *textures, char *line, int fd)
{
	int		i;
	int		j;
	char	*temp_we;

	j = 0;
	i = 0;
	if (ft_strncmp(&line[i], "WE", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_we = ft_strdup(avoid_whitespace(line + i));
		if (!temp_we)
		{
			closing(textures, fd, "Strdup error/ malloc\n");
			return ;
		}
		textures->permission = open(temp_we, O_RDONLY);
		checking_perm_for_west(temp_we, textures, j, fd);
	}
}
