/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_west.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:48:38 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/22 16:37:25 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_west_path(char *temp_we, t_textures *textures)
{
	if (ft_strncmp(temp_we, "textures/", 9) == 0)
	{
		textures->we = temp_we;
		textures->found_we += 1;
	}
	else
	{
		free(temp_we);
		printf("Failed textures\n");
		error_fun(textures);
	}
}

void	checking_perm_for_west(int permission,
		char *temp_we, t_textures *textures, int j)
{
	if (permission > 0)
	{
		if (check_if_png(temp_we))
		{
			while (temp_we[j] != '\0')
			{
				if (check_space(temp_we[j]))
				{
					free(temp_we);
					printf("Failed textures\n");
					error_fun(textures);
					return ;
				}
				j++;
			}
			checking_west_path(temp_we, textures);
		}
		close(permission);
	}
	else
	{
		free(temp_we);
		printf("Failed textures\n");
		error_fun(textures);
	}
}

void	we(t_textures *textures, char *line)
{
	int		i;
	int		j;
	int		permission;
	char	*temp_we;

	j = 0;
	i = 0;
	if (ft_strncmp(&line[i], "WE", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_we = ft_strdup(avoid_whitespace(line + i));
		if (!temp_we)
		{
			printf("Failed textures\n");
			error_fun(textures);
			return ;
		}
		permission = open(temp_we, O_RDONLY);
		checking_perm_for_west(permission, temp_we, textures, j);
	}
}
