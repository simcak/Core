#ifndef LIFE_H
# define LIFE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_life
{
	int		writing;
	int		width;
	int		height;
	int		gol;
	int		x;
	int		y;
} t_map;


#endif
