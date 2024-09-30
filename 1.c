// void count_lines(t_textures *textures, int fd) {
//     char *line;
//     int line_count = 0;

//     // Reset the file pointer to the start of the file if needed
//     // lseek(fd, 0, SEEK_SET); // Uncomment if using a file descriptor
    
//     while ((line = get_next_line(fd)) != NULL) {
//         // Count only non-empty lines
//         if (line[0] != '\n' && !check_space(line[0])) { // Assuming check_space function is defined
//             line_count++;
//         }
//         free(line); // Free the line after counting
//     }

//     textures->how_many_lines = line_count; // Store the line count in textures
// }

// void replacing_spaces_with_one(t_textures *textures) {
//     for (int i = 0; i < textures->how_many_lines; i++) {
//         if (textures->map[i]) {
//             int length = ft_strlen(textures->map[i]);
//             for (int j = 0; j < length; j++) {
//                 if (textures->map[i][j] == ' ' || textures->map[i][j] == '\t') {
//                     textures->map[i][j] = '1';
//                 }
//             }
//         }
//     }
// }

// void can_start_map(t_textures *textures, int fd) {
//     if (textures->found < 6) {
//         close(fd);
//         error_fun(textures);
//     }
//     textures->map = malloc(sizeof(char *) * (textures->how_many_lines + 1));
//     if (!textures->map) {
//         error_fun(textures);
//     }
//     textures->map[textures->how_many_lines] = NULL; // Null-terminate the map array
// }

// void parsing_map(t_textures *textures, char *line, int fd) {
//     int map_started = 0;
//     while (line != NULL) {
//         if (*line == '\n' && map_started) {
//             closing(textures, line, fd);
//         }
//         if (*line != '\n') {
//             map_started = 1;
//             textures->map_valid = checking_map(textures, line);
//             if (!textures->map_valid) {
//                 closing(textures, line, fd);
//             }
//             textures->map[textures->map_index] = ft_strdup(line);
//             if (!textures->map[textures->map_index]) {
//                 error_fun(textures);
//             }
//             textures->map_index++;
//         }
//         free(line);
//         line = get_next_line(fd);
//     }
// }

// void map_last(t_textures *textures, char *line, int fd) {
//     // First, count lines in the file
//     count_lines(textures, fd); // Count the lines before allocating

//     can_start_map(textures, fd); // Now allocate the map based on the counted lines
//     // Reset file pointer to the start of the file to read again
//     lseek(fd, 0, SEEK_SET); // Uncomment if you are using a file descriptor

//     // Now parse the map
//     parsing_map(textures, line, fd);
//     textures->how_many_lines = textures->map_index;

//     // Print the map lines
//     for (int i = 0; i < textures->how_many_lines; i++) {
//         printf("Map line %d: %s", i, textures->map[i]);
//     }

//     printf("\n");
//     replacing_spaces_with_one(textures);
//     printf("NEW\n");
//     for (int i = 0; i < textures->how_many_lines; i++) {
//         printf("Map line %d: %s", i, textures->map[i]);
//     }

//     if_new_line_in_middle(textures);
// }