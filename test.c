#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **map;
    int how_many_lines;
    int map_index;
} t_textures;

void print_map(t_textures *textures) {
    for (int i = 0; i < textures->how_many_lines; i++) {
        printf("%s\n", textures->map[i]);
    }
    printf("\n");
}

// Ensure all lines are of the same length by padding shorter lines with '1'
void pad_map_lines(t_textures *textures) {
    int max_length = 0;

    // Find the maximum line length
    for (int i = 0; i < textures->how_many_lines; i++) {
        int length = strlen(textures->map[i]);
        if (length > max_length) {
            max_length = length;
        }
    }

    // Pad shorter lines with '1'
    for (int i = 0; i < textures->how_many_lines; i++) {
        int length = strlen(textures->map[i]);
        if (length < max_length) {
            // Allocate new memory for the padded line
            char *padded_line = malloc(max_length + 1);
            strcpy(padded_line, textures->map[i]);
            // Fill the rest with '1'
            memset(padded_line + length, '0', max_length - length);
            padded_line[max_length] = '\0';
            // Replace the old line with the padded one
            free(textures->map[i]);
            textures->map[i] = padded_line;
        }
    }
}

// Flood fill function to mark all accessible spaces from the boundary
void flood_fill(t_textures *textures, int x, int y) {
    // Boundary check
    if (x < 0 || x >= textures->how_many_lines || y < 0 || y >= strlen(textures->map[x])) {
        return;
    }
    if (textures->map[x][y] == '1' || textures->map[x][y] == 'V' || textures->map[x][y] == 'N') {
        return;  // Stop if it's a wall, already visited, or invalid character
    }

    // Mark current position as visited
    textures->map[x][y] = 'V';  // Use 'V' to mark visited spaces

    // Recurse in all 4 directions
    flood_fill(textures, x + 1, y);  // Down
    flood_fill(textures, x - 1, y);  // Up
    flood_fill(textures, x, y + 1);  // Right
    flood_fill(textures, x, y - 1);  // Left
}

int map_closed(t_textures *textures) {
    // Ensure all map lines are of equal length
    pad_map_lines(textures);

    // Start flood fill from the edges where '0's are found
    for (int i = 0; i < textures->how_many_lines; i++) {
        if (textures->map[i][0] == '0') 
            flood_fill(textures, i, 0);  // Left edge
        if (textures->map[i][strlen(textures->map[i]) - 1] == '0')
            flood_fill(textures, i, strlen(textures->map[i]) - 1);  // Right edge
    }

    for (int j = 0; j < strlen(textures->map[0]); j++) {
        if (textures->map[0][j] == '0')
            flood_fill(textures, 0, j);  // Top edge
        if (textures->map[textures->how_many_lines - 1][j] == '0')
            flood_fill(textures, textures->how_many_lines - 1, j);  // Bottom edge
    }

    // Print the map after flood fill
    printf("Filled Map:\n");
    print_map(textures);

    // Check if any '0's remain unvisited, which means the map is not enclosed
    for (int i = 0; i < textures->how_many_lines; i++) {
        for (int j = 0; j < strlen(textures->map[i]); j++) {
            if (textures->map[i][j] == '0') {
                printf("Map is not fully enclosed. Open space at (%d, %d) accessible from the outside.\n", i, j);
                return 0;  // Map is not enclosed
            }
        }
    }

    printf("Map is fully enclosed.\n");
    return 1;  // Map is enclosed
}

int main() {
    t_textures textures;
    textures.how_many_lines = 14;
    textures.map_index = 0;

    // Example map with inconsistent lengths and invalid character ('N')
    textures.map = malloc(sizeof(char *) * textures.how_many_lines);
    textures.map[0] = strdup("1111111111111111111111111");
    textures.map[1] = strdup("1000000000110000000000001");
    textures.map[2] = strdup("1011000001110000000000001");
    textures.map[3] = strdup("1001000000000000000000001");
    textures.map[4] = strdup("111111111011000001110000000000001");
    textures.map[5] = strdup("100000000011000001110111111111111");
    textures.map[6] = strdup("11110111111111011100000010001");
    textures.map[7] = strdup("11110111111111011101010010001");
    textures.map[8] = strdup("11000000110101011100000010001");
    textures.map[9] = strdup("10000000000000001100000010001");
    textures.map[10] = strdup("10000000000000001101010010001");
    textures.map[11] = strdup("11000001110101011111011110N0111");
    textures.map[12] = strdup("111101111110101101111010001");
    textures.map[13] = strdup("111111111111111111111111111");

    printf("Original Map:\n");
    print_map(&textures);

    if (!map_closed(&textures)) {
        printf("Error: The map is not fully enclosed!\n");
    } else {
        printf("Success: The map is fully enclosed!\n");
    }

    // Free memory
    for (int i = 0; i < textures.how_many_lines; i++) {
        free(textures.map[i]);
    }
    free(textures.map);

    return 0;
}
