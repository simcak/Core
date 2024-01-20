#include <stdlib.h>
#include <stdio.h>
#include "flood_fill.h"

char	**make_area(char** zone, t_point size)
{
	char	**new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

int	main(void)
{
	t_point size = {16, 8};
	char *zone[] = {
		"1111111111111111",
		"1000100100010001",
		"1001010111000111",
		"1011010100110100",
		"1111100111100111",
		"1000010100010100",
		"1111010111010110",
		"1000100100110101",
	};

	char	**area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {7, 0};
	flood_fill(area, size, begin);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}
