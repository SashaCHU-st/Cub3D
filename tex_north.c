/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_north.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:46:14 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 13:53:17 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checking_north_path(char *temp_no, t_textures *textures)
{
	if (ft_strncmp(temp_no, "textures/", 9) == 0)
	{
		textures->no = temp_no;
		textures->found_no += 1;
	}
	else
	{
		free(temp_no);
		error_fun(textures);
	}
}

void	checking_perm_for_north(int permission,
		char *temp_no, t_textures *textures, int j)
{
	if (permission > 0)
	{
		if (check_if_png(temp_no))
		{
			while (temp_no[j] != '\0')
			{
				if (check_space(temp_no[j]))
				{
					free(temp_no);
					error_fun(textures);
					return ;
				}
				j++;
			}
			checking_north_path(temp_no, textures);
		}
		close(permission);
	}
	else
	{
		free(temp_no);
		error_fun(textures);
	}
}

void	no(t_textures *textures, char *line)
{
	int		i;
	int		j;
	int		permission;
	char	*temp_no;

	j = 0;
	i = 0;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_no = ft_strdup(avoid_whitespace(line + i));
		if (!temp_no)
		{
			error_fun(textures);
			return ;
		}
		permission = open(temp_no, O_RDONLY);
		checking_perm_for_north(permission, temp_no, textures, j);
	}
}
