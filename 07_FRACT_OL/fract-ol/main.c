/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:52:33 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/19 17:59:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	t_fractol	fractal;

	if (argc == 2 && fractol_strncmp(argv[1], "mandelbrot", 10)
		|| argc == 4 && fractol_strncmp(argv[1], "julia", 5))
	{
		fractal.name = argv[1];
		fractal_init(&fractal);
		fractal_render(&fractal, WIDTH, HEIGHT);
		mlx_loop(fractal.mlx);
	}
	else
		ft_error_exit(ERROR_ARGV);
}

/*
`mlx_init` is like starting the engine of your car before you can drive. 
When you call `mlx_init`, you're getting everything ready to create windows 
	and draw graphics on the screen. 
It sets up the connection between your program and the graphics system of 
	your computer. 
If `mlx_init` works, it gives you a "key" (a pointer) that you use to control
	the graphics you want to create.
If it doesn't work, it means something went wrong, and you can't start drawing.
*/