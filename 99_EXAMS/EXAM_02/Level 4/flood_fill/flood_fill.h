#ifndef FLOOD_FILL
# define FLOOD_FILL

typedef struct 	s_point {
    int 		x;				// x : Width  | x-axis
    int 		y;				// y : Height | y-axis
} 				t_point;

void	flood_fill(char **tab, t_point size, t_point begin);

#endif

