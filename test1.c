#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	int x;
	int y;
} t_point;

void	fill(char **tab, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x || tab[cur.y][cur.x] != to_fill)
		return;
	tab[cur.y][cur.x] = 'F';  // Fill the point with 'F'
	fill(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);
}

// Function to print the grid
void	print_tab(char **tab, t_point size)
{
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			printf("%c ", tab[i][j]);
		}
		printf("\n");
	}
}

// Function to allocate memory for the grid and initialize it
char **allocate_and_initialize_grid(char *grid[], t_point size)
{
	char **tab = malloc(size.y * sizeof(char *));
	for (int i = 0; i < size.y; i++)
	{
		tab[i] = malloc(size.x * sizeof(char));
		for (int j = 0; j < size.x; j++)
		{
			tab[i][j] = grid[i][j];
		}
	}
	return tab;
}

// Function to free the dynamically allocated grid
void free_grid(char **tab, t_point size)
{
	for (int i = 0; i < size.y; i++)
	{
		free(tab[i]);
	}
	free(tab);
}

int main(void)
{
	// Define the size of the grid
	t_point size = {8, 5};

	// Create a grid (2D array of chars)
	char *grid[] = {
		"11111111",
		"10001001",
		"10111001",
		"10000001",
		"11111111"
	};

	// Dynamically allocate and initialize the grid
	char **tab = allocate_and_initialize_grid(grid, size);

	// Print the original grid
	printf("Original grid:\n");
	print_tab(tab, size);

	// Define the starting point for the flood fill
	t_point begin = {2, 2}; // Start flood fill at (2, 2)

	// Call the flood fill function
	flood_fill(tab, size, begin);

	// Print the modified grid
	printf("\nModified grid:\n");
	print_tab(tab, size);

	// Free the allocated memory
	free_grid(tab, size);

	return 0;
}
