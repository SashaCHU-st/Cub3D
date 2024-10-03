
#include "cub3d.h"


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
	//		printf("Length %d\n", length);
		i++;
	}
	//printf("KUKU\n");
}
 //replacing with once everything befor

void replacing_spaces_with_one(t_textures *textures)
{
	for (int i = 0; i < textures->how_many_lines; i++)
	{
		if (textures->map[i])
		{
			int length = ft_strlen(textures->map[i]);
			for (int j = 0; j < length; j++)
			{
				if (textures->map[i][j] == ' ')
				{
					textures->map[i][j] = '1';
				}
			}
		}
	}
}
// void replacing_spaces_with_one_or_two(t_textures *textures)
// {
// 	int i, j;

// 	// Iterate over each row
// 	for (i = 0; i < textures->how_many_lines; i++)
// 	{
// 		if (textures->map[i])
// 		{
// 			int length = ft_strlen(textures->map[i]);

// 			// Iterate over each character in the row
// 			for (j = 0; j < length; j++)
// 			{
// 				if (textures->map[i][j] == ' ')
// 				{
// 					// Check if the space is on the outer boundary (first/last row or first/last column)
// 					if (i == 0 || i == textures->how_many_lines - 1 || j == 0 || j == length - 1)
// 					{
// 						// Space is on the boundary, replace with '2'
// 						textures->map[i][j] = '2';
// 					}
// 					else
// 					{
// 						// Check if space is surrounded by '1' (indicating it's inside the map)
// 						if ((textures->map[i - 1][j] == '1' || textures->map[i - 1][j] == ' ') &&
// 							(textures->map[i + 1][j] == '1' || textures->map[i + 1][j] == ' ') &&
// 							(textures->map[i][j - 1] == '1' || textures->map[i][j - 1] == ' ') &&
// 							(textures->map[i][j + 1] == '1' || textures->map[i][j + 1] == ' '))
// 						{
// 							// Space is surrounded by walls, replace with '1'
// 							textures->map[i][j] = '1';
// 						}
// 						else
// 						{
// 							// Otherwise, consider it as outside and replace with '2'
// 							textures->map[i][j] = '2';
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }


///replacing only inside
// void replacing_spaces_with_one(t_textures *textures)
// {
// 	int i = 0;
	
// 	while (i < textures->how_many_lines)
// 	{
// 		if (textures->map[i])
// 		{
// 			int length = ft_strlen(textures->map[i]);
// 			for (int j = 0; j < length; j++)
// 			{
// 				if (textures->map[i][j] == ' ' || textures->map[i][j] == '\t') {
// 					if (j > 0 && textures->map[i][j - 1] == '1' 
// 						&& j < length - 1 && textures->map[i][j + 1])
// 						textures->map[i][j] = '1';
// 				}
// 			}
// 			printf("Length1 %d\n", length);
// 		}
// 		i++;
// 	}
// }

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