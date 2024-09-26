/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:27:15 by aheinane          #+#    #+#             */
/*   Updated: 2024/09/26 12:36:44 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void error_fun()
{
	printf("Error\n");
	exit(1);
}

void closing(char *line, int fd)
{
	free(line);
	close(fd);
	error_fun();
}