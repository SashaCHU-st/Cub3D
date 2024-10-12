
#include "cub3d.h"

void	replacing_nl_with_zero(t_textures *textures)
{
	int i = 0;
	int length = 0;
	while (i < textures->how_many_lines)
	{
		if (textures->map[i])
		{
			length = ft_strlen(textures->map[i]);
			for (int j = 0; j < length; j++)
			{
				if (textures->map[i][j] == '\n')
					textures->map[i][j] = '\0';
			}
		}
					length = ft_strlen(textures->map[i]);
		i++;
	}
}

void replacing_spaces_with_one(t_textures *textures)
{
	int length = 0;
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		if (textures->map[i] != NULL)
		{
			length = ft_strlen(textures->map[i]);
			for (int j = 0; j < length; j++)
			{
				if (textures->map[i][j] == ' ')
					textures->map[i][j] = '1';
			}
		}
	}
	if (textures->how_many_lines > 0 && textures->map[textures->how_many_lines - 1] != NULL)
	{
		int length2 = ft_strlen(textures->map[textures->how_many_lines - 1]);
		for (int j = 0; j < length2; j++)
		{
			if (textures->map[textures->how_many_lines - 1][j] == ' ')
				textures->map[textures->how_many_lines - 1][j] = '1';
		}
	}
}


void if_new_line_in_middle(t_textures *textures)
{
	int i = 0;
	while (i < textures->how_many_lines)
	{
		if (textures->map[i][0] == '\0' || (textures->map[i][0] == '\n' && textures->map[i][1] == '\0'))
			error_fun(textures);
		i++;
	}
}