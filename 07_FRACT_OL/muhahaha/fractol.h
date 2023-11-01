/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:36:44 by nandroso          #+#    #+#             */
/*   Updated: 2023/10/31 19:15:26 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 800
# define HEIGHT 800

# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xFFFFFF
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF
# define COLOR_ELECTRIC_BLUE 0xFF00FFFF
# define COLOR_PURPLE_RAINBOW 0xEE82EE
# define COLOR_MUSHROOM_VIBES 0x66FF66
# define COLOR_DMT_TRIP 0x00FFFF00
# define COLOR_ACID_VISIONS 0xFF0000FF
# define COLOR_KALEIDOSCOPE 0xFFFFFF00
# define COLOR_UNIVERSE_EXPLORER 0x0000FFFF

typedef struct s_complex
{
	double	real;
	double	i;
}	t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	char		*name;
	void		*mlx_connection;
	void		*mlx_window;
	t_img		img;
	double		escape_value;
	int			iter_definition;
	double		shift_x;
	double		shift_y;
	double		zoom;
	double		julia_real;
	double		julia_i;
}	t_fractal;

double		atod(char *s);
double		map(double unsc_num, double new_min,
				double new_max, double old_max);
void		error(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		fractal_init(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
int			key_handle(int keysym, t_fractal *fractal);
int			exit_handle(t_fractal *fractal);
int			button_handle(int button, int x, int y, t_fractal *fractal);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

#endif
