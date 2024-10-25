/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:17:19 by aheinane          #+#    #+#             */
/*   Updated: 2024/10/24 13:39:23 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_exist(char *str)
{
	if (!str)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		*str = 0;
	}
	return (str);
}

char	*next_spot(char *storage)
{
	char	*next_spot;
	int		i;
	int		nextspot_index;

	i = 0;
	nextspot_index = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0' || storage[i + 1] == '\0')
	{
		free(storage);
		return (NULL);
	}
	next_spot = malloc(sizeof(char) * gnl_strlen(storage) - i);
	if (!next_spot)
		return (free_function(&storage));
	i++;
	while (storage[i])
		next_spot[nextspot_index++] = storage[i++];
	next_spot[nextspot_index] = '\0';
	free (storage);
	return (next_spot);
}

char	*ft_get_line(char *storage)
{
	char	*temp;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] != '\n')
		temp = malloc(i + 1);
	else
		temp = malloc(i + 2);
	i = 0;
	if (!temp)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
	{
		temp[i] = storage[i];
		i++;
	}
	if (storage[i] && storage[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

char	*ft_read(int fd, char *storage)
{
	char	*buffer;
	int		how_many_bytes;

	storage = ft_exist(storage);
	if (!storage)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_function(&storage));
	how_many_bytes = 1;
	while (how_many_bytes > 0 && !gnl_strchr(storage, '\n'))
	{
		how_many_bytes = read (fd, buffer, BUFFER_SIZE);
		if (how_many_bytes == -1)
			return (free_function(&storage));
		buffer[how_many_bytes] = '\0';
		storage = gnl_strjoin(storage, buffer);
		if (!storage)
			return (free_function(&storage));
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, 0, 0) < 0)
		return (free_function(&storage));
	storage = ft_read(fd, storage);
	if (!storage)
		return (free_function(&storage));
	line = ft_get_line(storage);
	storage = next_spot(storage);
	if (!line || !storage)
	{
		free(storage);
		storage = NULL;
	}
	return (line);
}
