/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/10 12:22:33 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ea(t_textures *textures, char *line)
{
	int i;
	int j;
	int permission;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "EA", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		textures->ea = ft_strdup(avoid_whitespace(line + i));
		if(!textures->ea)
			error_fun(textures);
		permission = open(textures->ea, O_RDONLY );
		if(permission > 0)
		{
			if (check_if_png(textures->ea))
			{
				j = 0;
				while (textures->ea[j] != '\0')
				{
					if (check_space(textures->ea[j]))
						error_fun(textures);
					j++;
				}
				if (ft_strncmp(textures->ea, "textures/", 2) == 0)
					textures->found_ea += 1;
			}
		}
		else
			error_fun(textures);
	}
}


void we(t_textures *textures, char *line)
{
	int i;
	int j;
	int permission;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "WE", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		textures->we = ft_strdup(avoid_whitespace(line + i));
		if(!textures->we)
			error_fun(textures);
		permission = open(textures->we, O_RDONLY );
		if(permission > 0)
		{
			if (check_if_png(textures->we))
			{
				j = 0;
				while (textures->we[j] != '\0')
				{
					if (check_space(textures->we[j]))
						error_fun(textures);
					j++;
				}
				if (ft_strncmp(textures->we, "textures/", 2) == 0)
					textures->found_we += 1;
			}
		}
		else
			error_fun(textures);
	}
}


void so(t_textures *textures, char *line)
{
	int i;
	int permission;
	int j;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "SO", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		textures->so = ft_strdup(avoid_whitespace(line + i));
		if(!textures->so)
			error_fun(textures);
		permission = open(textures->so, O_RDONLY );
		if(permission > 0)
		{
			if (check_if_png(textures->so))
			{
				j = 0;
				while (textures->so[j] != '\0')
				{
					if (check_space(textures->so[j]))
						error_fun(textures);
					j++;
				}
				if (ft_strncmp(textures->so, "textures/", 2) == 0)
					textures->found_so += 1;
			}
		}
		else
			error_fun(textures);
	}
}

void no(t_textures *textures, char *line)
{
	int i;
	int j;
	int permission;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && check_space(line[i + 2]))
	{
		i += 2;
		textures->no = ft_strdup(avoid_whitespace(line + i));
		if(!textures->no)
			error_fun(textures);
		permission = open(textures->no, O_RDONLY );
		if(permission > 0)
		{
			if (check_if_png(textures->no))
			{
				j = 0;
				while (textures->no[j] != '\0')
				{
					if (check_space(textures->no[j]))
						error_fun(textures);
					j++;
				}
				if (ft_strncmp(textures->no, "textures/", 2) == 0)
					textures->found_no += 1;
			}
		}
		else
			error_fun(textures);
	}
}


void	checking_textures(t_textures *textures, char *line)
{
	no(textures, line);
	so(textures, line);
	we(textures, line);
	ea(textures, line);
}
