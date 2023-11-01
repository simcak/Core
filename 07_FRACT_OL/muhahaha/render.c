/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:57:21 by nandroso          #+#    #+#             */
/*   Updated: 2023/10/31 17:57:33 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	man_or_jul(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->real = fractal->julia_real;
		c->i = fractal->julia_i;
	}
	else
	{
		c->real = z->real;
		c->i = z->i;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.real = (map(x, -2, 2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.i = (map(y, 2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	man_or_jul(&z, &c, fractal);
	while (i < fractal->iter_definition)
	{
		z = square_complex(z);
		z = sum_complex(z, c);
		if ((z.real * z.real) + (z.i * z.i) > fractal->escape_value)
		{
			color = map(i, COLOR_PURPLE_RAINBOW, COLOR_MUSHROOM_VIBES,
					fractal->iter_definition);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &fractal->img, COLOR_UNIVERSE_EXPLORER);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}
