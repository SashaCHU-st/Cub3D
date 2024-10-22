/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_south.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:09 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/22 16:37:10 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_south_path(char *temp_so, t_textures *textures)
{
	if (ft_strncmp(temp_so, "textures/", 9) == 0)
	{
		textures->so = temp_so;
		textures->found_so += 1;
	}
	else
	{
		free(temp_so);
		printf("Failed textures\n");
		error_fun(textures);
	}
}

void	checking_perm_for_south(int permission,
		char *temp_so, t_textures *textures, int j)
{
	if (permission > 0)
	{
		if (check_if_png(temp_so))
		{
			while (temp_so[j] != '\0')
			{
				if (check_space(temp_so[j]))
				{
					free(temp_so);
					printf("Failed textures\n");
					error_fun(textures);
					return ;
				}
				j++;
			}
			checking_south_path(temp_so, textures);
		}
		close(permission);
	}
	else
	{
		free(temp_so);
		printf("Failed textures\n");
		error_fun(textures);
	}
}

void	so(t_textures *textures, char *line)
{
	int		i;
	int		j;
	int		permission;
	char	*temp_so;

	i = 0;
	j = 0;
	if (ft_strncmp(&line[i], "SO", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_so = ft_strdup(avoid_whitespace(line + i));
		if (!temp_so)
		{
			printf("Failed textures\n");
			error_fun(textures);
			return ;
		}
		permission = open(temp_so, O_RDONLY);
		checking_perm_for_south(permission, temp_so, textures, j);
	}
}
