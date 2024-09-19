/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:53:02 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/19 14:41:47 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validation(t_textures *text)
{
	if (text->found_no && text->found_so && text->found_we && text->found_ea \
		&& text->found_c && text->found_f)
		text->found = 1;
	else
		text->found = 0;
	return (text->found);
}

void	open_close_file(char **argv, t_textures *textures)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0)
		error();
	while (line != NULL)
	{
		checking_textures(textures, line);
		
		checking_color(textures, line);
		free(line);
		line = get_next_line(fd);
	}
	// 	int i = 0;
	// while (textures->no[i] != '\0')  // Loop until the end of the string
	// {
	// 	int hehe = check_space(textures->no[i]);
	// 	printf("%d\n", hehe);  // Will print 1 if a space character is found, otherwise 0
	// 	i++;
	// }
	textures->map_valid = validation(textures);
	if (!textures->map_valid)
	{
		printf("Error\n");
		exit(1);
	}
	close(fd);
}
