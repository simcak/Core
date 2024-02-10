/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:52:33 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/23 17:56:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	t_fractol	fractal;

	if (correct_input_plus_set_data(argc, argv, &fractal))
	{
		fractal_init(&fractal);
		fractal_render(&fractal);
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