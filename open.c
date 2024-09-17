/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/17 11:12:13 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void open_close_file(char **argv)
{
	t_cub cub;
	
	int fd;
	char buffer[256];
	
	fd = open(argv[1], O_RDONLY);
	
	if(fd < 0)
	{
		printf("ERROOOOR");
		return;
	}
	ssize_t bytesRead;
	while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytesRead] = '\0';
		printf("%s", buffer);
	}
	close(fd);
}