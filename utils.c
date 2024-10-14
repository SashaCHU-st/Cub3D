/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:15:35 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/14 19:59:27 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

int	print_err_int(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}
