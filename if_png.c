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