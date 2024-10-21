/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/21 12:02:38 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void ea(t_textures *textures, char *line)
// {
// 	int i;
// 	int j;
// 	int permission;
// 	i = 0;
// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	if (ft_strncmp(&line[i], "EA", 2) == 0 && check_space(line[i + 2]))
// 	{
// 		i += 2;
// 		textures->ea = ft_strdup(avoid_whitespace(line + i));
// 		if(!textures->ea)
// 			error_fun(textures);
// 		permission = open(textures->ea, O_RDONLY );
// 		if(permission > 0)
// 		{
// 			if (check_if_png(textures->ea))
// 			{
// 				j = 0;
// 				while (textures->ea[j] != '\0')
// 				{
// 					if (check_space(textures->ea[j]))
// 						error_fun(textures);
// 					j++;
// 				}
// 				if (ft_strncmp(textures->ea, "textures/", 2) == 0)
// 					textures->found_ea += 1;
// 			}
// 		}
// 		else
// 			error_fun(textures);
// 	}
// }

void ea(t_textures *textures, char *line)
{
	int i = 0;
	int j = 0;
	int permission;
	char *temp_ea;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "EA", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_ea = ft_strdup(avoid_whitespace(line + i));
		if (!temp_ea)
		{
			error_fun(textures);
			return;
		}
		permission = open(temp_ea, O_RDONLY);
		if (permission > 0)
		{
			if (check_if_png(temp_ea))
			{
				while (temp_ea[j] != '\0')
				{
					if (check_space(temp_ea[j]))
					{
						free(temp_ea);
						error_fun(textures);
						return ;
					}
					j++;
				}
				if (ft_strncmp(temp_ea, "textures/", 9) == 0)
				{
					textures->ea = temp_ea;
					textures->found_ea += 1;
				}
				else
				{
					free(temp_ea);
					error_fun(textures);
				}
			}
			close(permission);
		}
		else
		{
			free(temp_ea);
			error_fun(textures);
		}
	}
}

void we(t_textures *textures, char *line)
{
	int i = 0;
	int j = 0;
	int permission;
	char *temp_we;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "WE", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_we = ft_strdup(avoid_whitespace(line + i));
		if (!temp_we)
		{
			error_fun(textures);
			return;
		}
		permission = open(temp_we, O_RDONLY);
		if (permission > 0)
		{
			if (check_if_png(temp_we))
			{
				while (temp_we[j] != '\0')
				{
					if (check_space(temp_we[j]))
					{
						free(temp_we);
						error_fun(textures);
						return ;
					}
					j++;
				}
				if (ft_strncmp(temp_we, "textures/", 9) == 0)
				{
					textures->we = temp_we;
					textures->found_we += 1;
				}
				else
				{
					free(temp_we);
					error_fun(textures);
				}
			}
			close(permission);
		}
		else
		{
			free(temp_we);
			error_fun(textures);
		}
	}
}



void so(t_textures *textures, char *line)
{
	int i = 0;
	int j = 0;
	int permission;
	char *temp_so;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "SO", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_so = ft_strdup(avoid_whitespace(line + i));
		if (!temp_so)
		{
			error_fun(textures);
			return;
		}
		permission = open(temp_so, O_RDONLY);
		if (permission > 0)
		{
			if (check_if_png(temp_so))
			{
				while (temp_so[j] != '\0')
				{
					if (check_space(temp_so[j]))
					{
						free(temp_so);
						error_fun(textures);
						return ;
					}
					j++;
				}
				if (ft_strncmp(temp_so, "textures/", 9) == 0)
				{
					textures->so = temp_so;
					textures->found_so += 1;
				}
				else
				{
					free(temp_so);
					error_fun(textures);
				}
			}
			close(permission);
		}
		else
		{
			free(temp_so);
			error_fun(textures);
		}
	}
}

void no(t_textures *textures, char *line)
{
	int i = 0;
	int j = 0;
	int permission;
	char *temp_no;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		temp_no = ft_strdup(avoid_whitespace(line + i));
		if (!temp_no)
		{
			error_fun(textures);
			return;
		}
		permission = open(temp_no, O_RDONLY);
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
			close(permission);
		}
		else
		{
			free(temp_no);
			error_fun(textures);
		}
	}
}


void	checking_textures(t_textures *textures, char *line)
{
	no(textures, line);
	so(textures, line);
	we(textures, line);
	ea(textures, line);
}
