/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:51:09 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/28 11:40:40 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		i++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*free_function(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	new = malloc(sizeof(char) * ((gnl_strlen(s1) + gnl_strlen(s2)) + 1));
	if (!new)
		return (free_function(&s1));
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}
