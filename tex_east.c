/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_east.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:47:55 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/23 09:10:11 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_east_path(char *temp_ea, t_textures *textures)
{
	if (ft_strncmp(temp_ea, "textures/", 9) == 0)
	{
		textures->ea = temp_ea;
		textures->found_ea += 1;
	}
	else
	{
		free(temp_ea);
		printf("Wrong path\n");
		error_fun(textures);
	}
}

void	checking_perm_for_east(int permission,
		char *temp_ea, t_textures *textures, int j)
{
	if (permission > 0)
	{
		if (check_if_png(temp_ea))
		{
			while (temp_ea[j] != '\0')
			{
				if (check_space(temp_ea[j]))
				{
					free(temp_ea);
					printf("Wrong textures element\n");
					error_fun(textures);
					return ;
				}
				j++;
			}
			checking_east_path(temp_ea, textures);
		}
		close(permission);
	}
	else
	{
		free(temp_ea);
		printf("No permission\n");
		error_fun(textures);
	}
}

void	ea(t_textures *textures, char *line)
{
	int		i;
	int		j;
	int		permission;
	char	*temp_ea;

	i = 0;
	j = 0;
	if (ft_strncmp(&line[i], "EA", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_ea = ft_strdup(avoid_whitespace(line + i));
		if (!temp_ea)
		{
			printf("Strdup error/ malloc\n");
			error_fun(textures);
			return ;
		}
		permission = open(temp_ea, O_RDONLY);
		checking_perm_for_east(permission, temp_ea, textures, j);
	}
}
