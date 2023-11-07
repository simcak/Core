/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:52:33 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/07 19:19:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR	1
#define WIDTH 			700
#define HEIGHT 			900

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window_1;
	void	*mlx_window_2;
	
	// starting the connection with the grafical server = starting the machine
	mlx_connection = mlx_init();
	if (mlx_connection == NULL)
		return (MALLOC_ERROR);

	// vytvoření okna = je třeba kompilace
	mlx_window_1 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "muhaha");
	if (mlx_window_1 == NULL)
	{
		mlx_destroy_display(mlx_connection);
		free (mlx_window_1);
		return (MALLOC_ERROR);
	}

	mlx_window_2 = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "2haha");
	if (mlx_window_2 == NULL)
	{
		mlx_destroy_display(mlx_connection);
		free (mlx_window_2);
		return (MALLOC_ERROR);
	}

	for (int i = WIDTH * 0.1; i < WIDTH * 0.9; i++)
		for (int j = HEIGHT * 0.1; j < HEIGHT * 0.9; j++)
			mlx_pixel_put(mlx_connection, mlx_window_1, i, j, 0xff0000);

	// aby se okno hned nezavřelo, hodíme ho do loopy
	mlx_loop(mlx_connection);

	return (0);
}
