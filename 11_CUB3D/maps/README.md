## Explanation of the .cub files and the map creation logic

1. **Texture Paths**: These specify the file paths for the textures used for the walls in different directions (North, South, West, East).
	```
	NO ./map_textures/orange_bricks.png
	SO ./map_textures/stone_bricks.png
	WE ./map_textures/game_bricks.png
	EA ./map_textures/old_bricks.png
	```

2. **Floor and Ceiling Colors**: These specify the RGB values for the floor and ceiling colors.
	```
	F 220,100,0
	C 225,30,0
	```

3. **Map Layout**: This is a grid representation of the map where each character represents a different element:
	- `1` represents a wall.
	- `0` represents an empty space.
	- `N`, `S`, `E`, `W` represent the starting positions - facing either North, South, East, or West.
	- Other characters (like `X`, `C`, `D`, `H`) in some maps indicate invalid or special elements.

### Example Map Breakdown

For the map in `DEF_MAP.CUB`:
```
NO ./map_textures/NO.xpm
SO ./map_textures/SO.xpm
WE ./map_textures/WE.xpm
EA ./map_textures/EA.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

- **Textures**: The textures for the walls are specified for each direction.
- **Colors**: The floor color is `220,100,0` and the ceiling color is `225,30,0`.
- **Map Layout**: The grid shows the layout of the walls (`1`), empty spaces (`0`), and the starting position (`N` for North).

### Logic

1. **Parsing**: The game engine reads the map file, parsing the texture paths, colors, and the map layout.
2. **Rendering**: Based on the parsed data, the engine loads the textures and colors, and renders the map grid.
3. **Gameplay**: The player starts at the specified position (e.g., `N` for North) and navigates through the map, interacting with walls and empty spaces.

### Validation

Some maps include invalid configurations:
- **INVALID_MISSING_WALL.CUB**: Missing wall in the layout.
- **INVALID_DUPLICATE_START.CUB**: Multiple starting positions.
- **INVALID_CHARS.CUB**: Contains invalid characters.

These maps will cause errors or be rejected by the game engine during the parsing or validation phase.