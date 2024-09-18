/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:11:07 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/18 11:31:41 by aheinane         ###   ########.fr       */
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

void	checking_textures(char *line)
{
	t_textures	text;

	if (ft_strncmp(line, "NO", 2) == 0 && &check_space)
	{
		text.no = ft_strdup(avoid_whitespace(line + 2 + 1));
		printf("NORTH: \n %s\n", text.no);
	}
	if (ft_strncmp(line, "SO", 2) == 0 && &check_space)
	{
		text.so = ft_strdup(avoid_whitespace(line + 2 + 1));
		printf("SOUTH: \n %s\n", text.so);
	}
	if (ft_strncmp(line, "WE", 2) == 0 && &check_space)
	{
		text.we = ft_strdup(avoid_whitespace(line + 2 + 1));
		printf("WEST : \n %s\n", text.we);
	}
	if (ft_strncmp(line, "EA", 2) == 0 && &check_space)
	{
		text.ea = ft_strdup(avoid_whitespace(line + 2 + 1));
		printf("EAST: \n %s\n", text.ea);
	}
}
