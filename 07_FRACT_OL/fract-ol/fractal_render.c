/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:02:49 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/21 21:44:08 by psimcak          ###   ########.fr       */
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
static void	calculate_pxl(int width, int height, t_fractol *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.re = 0.0;
	z.im = 0.0;
	c.re = resize(width, -2, 2, WIDTH);
	c.im = resize(height, 2, -2, HEIGHT);
	for (i = 0; i < fractal->iteration_threshold; i++)
	{
		z = ft_sum_complex(ft_sqr_complex(z), c);
		if ((z.re * z.re) + (z.im * z.im) > fractal->edge)
		{
			color = resize(i, BLACK, WHITE, fractal->iteration_threshold);
			ft_pxl_put(&fractal->img, width, height, color);
			return ;
		}
	}
	ft_pxl_put(&fractal->img, width, height, OUTRAGEOUS_ORANGE);
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

	for (height = 0; height < HEIGHT; height++)
		for (width = 0; width < WIDTH; width++)
			calculate_pxl(width, height, fractal);

	mlx_put_image_to_window(fractal->mlx,
							fractal->mlx_win,
							fractal->img.img_ptr,
							0, 0);
}
