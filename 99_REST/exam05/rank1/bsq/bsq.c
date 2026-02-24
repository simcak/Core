#include "bsq.h"

// ---------------------------- helper functions ---------------------------- //
void	free_map(char** arr)
{
	if (arr)
	{
		for (int i = 0; arr[i] != NULL; i++)
			if(arr[i])
				free(arr[i]);
		free(arr);
	}
}

void	free_all(char** arr, char* line)
{
	free_map(arr);
	if (line)
		free(line);
}

// ------------------------ loadMap helper functions ------------------------ //
char*	ft_substr(const char* arr, int start, int len)
{
	char	*str = malloc((size_t)len + 1);
	if (!str) return NULL;

	for (int k = 0; k < len; ++k)
		str[k] = arr[start + k];

	str[len] = '\0';
	return str;
}

int	element_control(char** map, char c1, char c2)
{
	for (int i = 0; map[i]; ++i)
		for (int j = 0; map[i][j]; j++)
			if ((map[i][j] != c1) && (map[i][j] != c2))
				return -1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Loads the elements from the file ptr into the t_elements structure.
 */
int	loadElements(FILE* file, t_elements* elements)
{
	int	ret = fscanf(file, "%d %c %c %c", &(elements->n_lines), &(elements->empty), &(elements->obstacle), &(elements->full));

	if (ret != 4)
		return -1;

	if (elements->n_lines <= 0)
		return -1;
	if (elements->empty == elements->obstacle || elements->empty == elements->full || elements->obstacle == elements->full)
		return -1;
	if (elements->empty < 32 || elements->empty > 126)
		return -1;
	if (elements->obstacle < 32 || elements->obstacle > 126)
		return -1;
	if (elements->full < 32 || elements->full > 126)
		return -1;

	return 0;
}

/**
 * @brief Loads the map from the file pointer into the t_map structure.
 */
int	loadMap(FILE* file, t_map* map, t_elements* elements)
{
	map->height = elements->n_lines;
	map->grid = calloc((size_t)map->height + 1, sizeof(char *));
	if (!map->grid)
		return -1;

	char*	line = NULL;
	size_t	len = 0;

	if (getline(&line, &len, file) == -1)
		return (free_all(map->grid, line), -1);

	for (int i = 0; i < map->height; i++)
	{
		int	read = getline(&line, &len, file);

		if (read == -1)
			return (free_all(map->grid, line), -1);
		if (line[read - 1] == '\n')
			read--;
		else
			return (free_all(map->grid, line), -1);

		map->grid[i] = ft_substr(line, 0, read);

		if (!(map->grid[i]))
			return (free_all(map->grid, line), -1);

		if (i == 0)
			map->width = read;
		else if (map->width != read)
			return (free_all(map->grid, line), -1);
	}
	if (element_control(map->grid, elements->empty, elements->obstacle) == -1) 
		return (free_all(map->grid, line), -1);
	free(line);

	return 0;
}

void	print_filled_square(t_map* map, t_square* square, t_elements* elements)
{
	for (int i = square->i; i < square->i + square->size; i++)
		for (int j = square->j; j < square->j + square->size; j++)
			if ((i < map->height) && (j < map->width)) // necessary?
				map->grid[i][j] = elements->full;

	for (int i = 0; i < map->height; i++)
	{
		fputs(map->grid[i], stdout);
		fputs("\n", stdout);
	}
}

// -------------------- find_big_square helper function --------------------- //
int	find_min(int n1, int n2, int n3)
{
	int	min = n1;

	if (n2 < min)
		min = n2;
	if (n3 < min)
		min = n3;
	return min;
}

/**
 * @brief Finds the biggest square in the map using dynamic programming.
 * 
 * It fills a matrix where each cell contains the size of the biggest square
 * that can be formed with the cell as the bottom-right corner. It updates the
 * square structure with the size and position of the biggest square found.
 */
void	find_big_square(t_map* map, t_square* square, t_elements* elements)
{
	int	matrix[map->height][map->width];

	for (int i = 0; i < map->height; i++)
		for (int j = 0; j < map->width; j++)
			matrix[i][j] = 0;

	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (map->grid[i][j] == elements->obstacle)
				matrix[i][j] = 0;
			else if (i == 0 || j == 0)
				matrix[i][j] = 1;
			else {
				int min = find_min(matrix[i - 1][j],matrix[i - 1][j - 1], matrix[i][j - 1]);
				matrix[i][j] = min + 1;
			}

			if (matrix[i][j] > square->size)
			{
				square->size = matrix[i][j];
				square->i = i - matrix[i][j] + 1;
				square->j = j - matrix[i][j] + 1;
			}
		}
	}
}

/**
 * Main function to execute the BSQ algorithm on a given file pointer.
 * It loads the elements and the map, finds the biggest square, prints it, and
 * frees the allocated memory for the map.
 */
int	execute_bsq(FILE* file)
{
	t_elements	elements;
	if (loadElements(file, &elements) == -1)
		return -1;

	t_map		map;
	if (loadMap(file, &map, &elements) == -1)
		return -1;

	t_square	square;
	square.size = 0; square.i = 0; square.j = 0;
	find_big_square(&map, &square, &elements);
	print_filled_square(&map, &square, &elements);
	free_map(map.grid);
	return 0;
}

/**
 * Converts a file name to a file pointer and executes the main BSQ algorithm on
 * it.
 */
int	convert_file_pointer(char* name)
{
	int		ret = 0;
	FILE*	file = fopen(name, "r");

	if(!file)
		return -1;
	ret = execute_bsq(file);
	fclose(file);
	return ret;
}
