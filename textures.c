/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/19 14:54:10 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || \
		ch == '\f' || ch == '\v')
		return (1);
	return (0);
}

char	*avoid_whitespace(char *str)
{
	char	*end;

	while (check_space((char)*str))
		str++;
	if (*str == '\0')
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && check_space((char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

void we_ea(t_textures *textures, char *line)
{
	int i = 0;
	if (ft_strncmp(line, "WE", 2) == 0 && check_space(line[2]))
	{
		textures->we = ft_strdup(avoid_whitespace(line + 2));
		i = 0;
		while (textures->we[i] != '\0')
		{
			
			if(check_space(textures->we[i]))
			{
				printf("Error\n");
				exit(1);
			}
			i++;
		}
		if(ft_strncmp(textures->we, "./", 2) == 0 )
		{
			textures->found_we = 1;
			printf("WEST: %s\n", textures->we);
		}
		else
			error();
	}
	if (ft_strncmp(line, "EA", 2) == 0 && check_space(line[2]))
	{
		textures->ea = ft_strdup(avoid_whitespace(line + 2));
		i = 0;
		while (textures->ea[i] != '\0')
		{
			
			if(check_space(textures->ea[i]))
			{
				printf("Error\n");
				exit(1);
			}
			i++;
		}
		if(ft_strncmp(textures->ea, "./", 2) == 0 )
		{
			textures->found_ea = 1;
			printf("EAST: %s\n", textures->ea);
		}
		else
			error();
	}
}

void no_so(t_textures *textures, char *line)
{
	int i = 0;
	if (ft_strncmp(line, "NO", 2) == 0 && check_space(line[2]))
	{
		textures->no = ft_strdup(avoid_whitespace(line + 2));
		i = 0;
		while (textures->no[i] != '\0')
		{
			
			if(check_space(textures->no[i]))
			{
				printf("Error\n");
				exit(1);
			}
			i++;
		}
		if(ft_strncmp(textures->no, "./", 2) == 0 )
		{
			textures->found_no = 1;
			printf("NORTH: %s\n", textures->no);
		}
		else
			error();
	}
	if (ft_strncmp(line, "SO", 2) == 0 && check_space(line[2]))
	{
		textures->so = ft_strdup(avoid_whitespace(line + 2));
		i = 0;
		while (textures->so[i] != '\0')
		{
			
			if(check_space(textures->so[i]))
			{
				printf("Error\n");
				exit(1);
			}
			i++;
		}
		if(ft_strncmp(textures->so, "./", 2) == 0 )
		{
			textures->found_so = 1;
			printf("SOUTH: %s\n", textures->so);
		}
		else
			error();
	}
}

void	checking_textures(t_textures *textures, char *line)
{
	no_so(textures, line);
	we_ea(textures, line);
	// int i = 0;
	// while (textures->no[i] != '\0')  // Loop until the end of the string
	// {
	// 	int hehe = check_space(textures->no[i]);
	// 	printf("%d\n", hehe);  // Will print 1 if a space character is found, otherwise 0
	// 	i++;
	// }

}