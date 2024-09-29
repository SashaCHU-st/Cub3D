/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/29 17:45:03 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ea(t_textures *textures, char *line)
{
	int i;
	i =0;
	if (ft_strncmp(line, "EA", 2) == 0 && check_space(line[2]))
	{
		textures->ea = ft_strdup(avoid_whitespace(line + 2));
		if(check_if_png(textures->ea))
		{
			while (textures->ea[i] != '\0')
			{
				
				if(check_space(textures->ea[i]))
					error_fun(textures);;
				i++;
			}
			if(ft_strncmp(textures->ea, "./", 2) == 0 )
			{
				textures->found_ea += 1;
				printf("EAST: %s\n", textures->ea);
			}
		}
		else
			error_fun(textures);;
	}
}


void	we(t_textures *textures, char *line)
{
	int i;
	i = 0;
	if (ft_strncmp(line, "WE", 2) == 0 && check_space(line[2]))
	{
		textures->we = ft_strdup(avoid_whitespace(line + 2));
		if(check_if_png(textures->we))
		{
			while (textures->we[i] != '\0')
			{
				
				if(check_space(textures->we[i]))
					error_fun(textures);;
				i++;
			}
			if(ft_strncmp(textures->we, "./", 2) == 0 )
			{
				textures->found_we += 1;
				printf("WEST: %s\n", textures->we);
			}
		}
		else
			error_fun(textures);;
	}
}


void	so(t_textures *textures, char *line)
{
	int i ;
	i = 0;
	if (ft_strncmp(line, "SO", 2) == 0 && check_space(line[2]))
	{
		textures->so = ft_strdup(avoid_whitespace(line + 2));
		if(check_if_png(textures->so))
		{
			while (textures->so[i] != '\0')
			{
				
				if(check_space(textures->so[i]))
					error_fun(textures);;
				i++;
			}
			if(ft_strncmp(textures->so, "./", 2) == 0 )
			{
				textures->found_so += 1;
				printf("SOUTH: %s\n", textures->so);
			}
		}
		else
			error_fun(textures);;
	}
}

void	no(t_textures *textures, char *line)
{
	int i = 0;
	if (ft_strncmp(line, "NO", 2) == 0 && check_space(line[2]))
	{
		i = 0;
		textures->no = ft_strdup(avoid_whitespace(line + 2));
		if(check_if_png(textures->no))
		{
			while (textures->no[i] != '\0')
			{
				if(check_space(textures->no[i]))
					error_fun(textures);;
				i++;
			}
			if(ft_strncmp(textures->no, "./", 2) == 0 )
			{
				textures->found_no += 1;
				printf("NORTH: %s\n", textures->no);
			}
		}
		else
			error_fun(textures);;
	}
}

void	checking_textures(t_textures *textures, char *line)
{
	no(textures, line);
	so(textures, line);
	we(textures, line);
	ea(textures, line);
	
}
