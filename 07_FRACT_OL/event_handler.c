/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:36:31 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/24 15:18:11 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_destroyer(t_fractol *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx, fractal->mlx_win);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(EXIT_SUCCESS);
}

int	ft_key_handler(int keysym, t_fractol *fractal)
{
	if (keysym == XK_Escape)
		ft_destroyer(fractal);
	else if (keysym == XK_Left)
		fractal->shift_re += 0.2 * fractal->zoom;
	else if (keysym == XK_Right)
		fractal->shift_re -= 0.2 * fractal->zoom;
	else if (keysym == XK_Up)
		fractal->shift_im -= 0.2 * fractal->zoom;
	else if (keysym == XK_Down)
		fractal->shift_im += 0.2 * fractal->zoom;
	else if (keysym == XK_plus || keysym == 65451)
		fractal->iteration_threshold += 10;
	else if (keysym == XK_minus || keysym == 65453)
		fractal->iteration_threshold -= 10;
	fractal_render(fractal);
	return (0);
}

int	ft_button_handler(int button, int x, int y, t_fractol *fractal)
{
	if (button == Button4)
		fractal->zoom *= 0.95;
	else if (button == Button5)
		fractal->zoom += 0.5;
	fractal_render(fractal);
	return (0);
}

int	julia_track(int x, int y, t_fractol *fractal)
{
	if (fractol_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_re = (fractal->zoom * resize(x, -2, 2, WIDTH))
			+ fractal->shift_re;
		fractal->julia_im = (fractal->zoom * resize(y, 2, -2, HEIGHT))
			+ fractal->shift_im;
		fractal_render(fractal);
	}
	return (0);
}
