/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:02:49 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/22 18:47:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_pxl_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pxl_ptr + offset) = color;
}

/*
MANDELBROT:		z = z^2 + c
				z is (0, 0)
				c is pixel by pixel the actual point in complex area
*/
static void	pxl_render(int width, int height, t_fractol *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.re = 0.0;
	z.im = 0.0;
	c.re = fractal->zoom * resize(width, -2, 2, WIDTH) + fractal->shift_re;
	c.im = fractal->zoom * resize(height, 2, -2, HEIGHT) + fractal->shift_im;
	while (i < fractal->iteration_threshold)
	{
		z = ft_sum_complex(ft_sqr_complex(z), c);
		if ((z.re * z.re) + (z.im * z.im) > fractal->edge)
		{
			color = resize(i, BLACK, WHITE, fractal->iteration_threshold);
			ft_pxl_put(&fractal->img, width, height, color);
			return ;
		}
		i++;
	}
	ft_pxl_put(&fractal->img, width, height, BLACK);
}

/*
The fractal_render function iterates over every pixel on the screen, 
applying handle_pixel to render the fractal, and then displays the image 
on the window.
*/
void	fractal_render(t_fractol *fractal)
{
	int	width;
	int	height;

	height = 0;
	while (height++ < HEIGHT)
	{
		width = 0;
		while (width++ < WIDTH)
			pxl_render(width, height, fractal);
	}

	mlx_put_image_to_window(fractal->mlx,
							fractal->mlx_win,
							fractal->img.img_ptr,
							0, 0);
}
