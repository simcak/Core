/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:13:55 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/23 19:37:26 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	necessary_evil_1(t_fractol *fractal)
{
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	ft_error_exit(ERROR_MALLOC);
}

static void	necessary_evil_2(t_fractol *fractal)
{
	mlx_destroy_window(fractal->mlx, fractal->mlx_win);
	necessary_evil_1(fractal);
}

static void	data_init(t_fractol *fractal)
{
	fractal->edge = 4.0;
	fractal->iteration_threshold = 42;
	fractal->shift_re = 0.0;
	fractal->shift_im = 0.0;
	fractal->zoom = 1.0;
}

/*
listen for the input.
hooks_init() takes key-numbers and operates by this info
Key is input from KEYboard
Button is input from the mouse
*/
static void	hooks_init(t_fractol *fractal)
{
	mlx_hook(fractal->mlx_win, DestroyNotify, StructureNotifyMask,
		ft_destroyer, fractal);
	mlx_hook(fractal->mlx_win, KeyPress, KeyPressMask,
		ft_key_handler, fractal);
	mlx_hook(fractal->mlx_win, ButtonPress, ButtonPressMask,
		ft_button_handler, fractal);
	mlx_hook(fractal->mlx_win, MotionNotify, PointerMotionMask,
		julia_track, fractal);
}

void	fractal_init(t_fractol *fractal)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		ft_error_exit(ERROR_MALLOC);
	fractal->mlx_win = mlx_new_window(fractal->mlx, WIDTH, HEIGHT,
			fractal->name);
	if (fractal->mlx_win == NULL)
		necessary_evil_1(fractal);
	fractal->img.img_ptr = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
		necessary_evil_2(fractal);
	fractal->img.pxl_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp,
			&fractal->img.line_len,
			&fractal->img.endian);
	data_init(fractal);
	hooks_init(fractal);
}
