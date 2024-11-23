# Cub3D
Cub3D is the second graphic project written in C, using the MLX42 library. 

It is built using the Ray-Casting technique, rendering scenes from a first-person perspective. 

Textures are displayed based on the player's viewpoint.
![Cub3d](https://github.com/user-attachments/assets/f15e3599-3d3d-4231-9715-a59b87f679f4)

## Configuartion file
Configuration file need to include:
1. path to the textures
2. floor and ceiling colors
3. map itself
```bash
NO textures/no_wall.png
SO textures/so_wall.png
WE textures/we_wall.png
EA textures/ea_wall.png

F 25, 255, 100
C 220,30,0 

111111111
100000001
100000001
100000001
100S00001
100000001
100000001
100000001
111111111
```

## Controls
- W,D or Arrow keys up, down: Move forward and back.
- A, D: move to the left and right.
- Arrow Keys or Mouse: Rotate the player's view.
- ESC Quit the game.

## Cub3D Program Usage
1. Clone repository
2. Move to directory
```bash
cd cub3D
```
3.Run make file
```bash
make
```
4. Run th program : example
```bash
./cub3D maps/valid/good1.cub
```
