/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/19 10:18:44 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int  validation(t_textures *text)
{
	if (text->found_no && text->found_so && text->found_we && text->found_ea \
		&& text->found_c && text->found_f)
	{
		text->found = 1;
		//printf("All directions are found\n");
	}
	else
	{
		text->found = 0;
	}
	return (text->found);
}


void open_close_file(char **argv, t_textures *textures)
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
		checking_textures(textures, line);
		checking_color(textures, line);
		textures->map_valid = validation(textures);
		free(line);
	}
	//printf("%d\n", textures->floor_r);
	if (textures->map_valid)
		printf("All directions are found\n");
	else
	{
		printf("NOT VALID!\n");
		exit(1);
	}
	close(fd);
}
