
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
			printf("Length %d\n", length);
		i++;
	}
	//printf("KUKU\n");
}

void	replacing_spaces_with_one(t_textures *textures)
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
				if ((textures->map[i][j] == ' ' || textures->map[i][j] == '\t') && (textures->map[i][j - 1] == '1' && textures->map[i][j + 1]))
					textures->map[i][j] = '1';
			}
		}
		length = ft_strlen(textures->map[i]);
		printf("Length1 %d\n", length);
		i++;
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