
#include "cub3d.h"

int	map_closed(t_textures *textures)
{
	int i, j, len_current, len_next;
	int last_index = textures->how_many_lines - 1;
	i = 0;
	while (textures->map[0][i])
	{
		if (textures->map[0][i] != '1')
			return 0;
		i++;
	}
	i = 0;
	while (textures->map[last_index][i])
	{
		if (textures->map[last_index][i] != '1')
		{
			printf("kuku from the bottom\n");
			return 0;
		}
		i++;
	}
	i = 0;
	while (i < last_index)
	{
		len_current = ft_strlen(textures->map[i]);
		len_next = ft_strlen(textures->map[i + 1]);
		if (textures->map[i][0] != '1' || textures->map[i][len_current - 1] != '1')
		{
			printf("kukuf from sides\n");
			return 0;
		}
		if (len_current < len_next)
		{
			j = len_current;
			while (j < len_next)
			{
				if (textures->map[i + 1][j] != '1')
				{
					printf("kuku from not perfect rect upper side");
					return 0;
				}
				j++;
			}
		}
		if (len_current < len_next)
		{
			j = len_current;
			while (j < len_next)
			{
				if (textures->map[i + 1][j] != '1')
				{
					printf("kuku from upper(i) is shorter then lower line(i+1)\n");
					return 0;
				}
				j++;
			}
		}
		else if (len_current > len_next)
		{
			j = len_next;	
			while (j < len_current)
			{
				if (textures->map[i][j] != '1')
				{
					printf("kuku from upper(i) is longer then lower line(i+1)\n");
					return 0;
				}
				j++;
			}
		}
	i++;
	}
	return 1;
}