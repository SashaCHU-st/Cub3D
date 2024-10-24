/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_png.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:18:35 by mspasic           #+#    #+#             */
/*   Updated: 2024/10/14 20:18:42 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_png(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i == 0)
		return (0);
	if (str[i - 1] == 'g' && str[i - 2] == 'n' && \
		str[i - 3] == 'p' && str[i - 4] == '.' && \
		i - 4 != 0)
		return (1);
	else
		return (0);
}
