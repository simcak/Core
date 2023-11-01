/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:57:59 by nandroso          #+#    #+#             */
/*   Updated: 2023/10/31 19:26:20 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	exit_handle(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	button_handle(int button, int x, int y, t_fractal *fractal)
{
	x = 0;
	y = 0;
	if (button == Button4)
		fractal->zoom *= 0.95;
	else if (button == Button5)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}

int	key_handle(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		exit_handle(fractal);
	else if (keysym == XK_a || keysym == XK_Left)
		fractal->shift_x -= (0.15 * fractal->zoom);
	else if (keysym == XK_d || keysym == XK_Right)
		fractal->shift_x += (0.15 * fractal->zoom);
	else if (keysym == XK_w || keysym == XK_Up)
		fractal->shift_y += (0.15 * fractal->zoom);
	else if (keysym == XK_s || keysym == XK_Down)
		fractal->shift_y -= (0.15 * fractal->zoom);
	else if (keysym == XK_plus)
		fractal->iter_definition += 10;
	else if (keysym == XK_minus)
		fractal->iter_definition -= 10;
	fractal_render(fractal);
	return (0);
}
