/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/18 11:24:17 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void open_close_file(char **argv)
{
	int fd;
	char *line;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR: Could not open the file.\n");
		return;
	}
	while ((line = get_next_line(fd)) != NULL)
	{	
		checking_textures(line);
		free(line);
	}
	close(fd);
}