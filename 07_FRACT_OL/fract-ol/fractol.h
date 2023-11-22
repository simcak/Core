/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:25:08 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/22 18:19:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc free
# include <unistd.h> // write, constands
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define ERROR_ARGV \
"Please enter: \t./fractol mandelbrot \n\t\tOR \
\n\t\t./fractol julia <value_1> <value_2>\n"
# define ERROR_MALLOC \
"Problems with malloc()"

// WINDOW SIZE
# define WIDTH	900
# define HEIGHT	900

// COLORS
// basic ones
# define BLACK				0x000000	// RGB(0, 0, 0)
# define WHITE				0xFFFFFF	// RGB(255, 255, 255)
# define RED				0xFF0000	// RGB(255, 0, 0)
# define GREEN				0x00FF00	// RGB(0, 255, 0)
# define BLUE				0x0000FF	// RGB(0, 0, 255)
// cool ones
# define DEEP_SPACE_SPARKLE	0x4A646C
# define ELECTRIC_BLUE		0x7DF9FF
# define NEON_GREEN			0x39FF14
# define ELECTRIC_PURPLE	0xBF00FF
# define CYBER_GRAPE		0x58427C
# define TURQUOISE_BLUE		0x00FFEF
# define PHTHALO_BLUE		0x000F89
# define HOT_MAGENTA		0xFF1DCE
# define NEON_FUCHSIA		0xFE4164
# define OUTRAGEOUS_ORANGE	0xFF6E4A

// STRUCTURES
typedef struct s_complex
{
	double		re;
	double		im;
}				t_complex;

typedef struct s_img
{
	void		*img_ptr;
	char		*pxl_ptr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

/*
typedef struct	s_img
{
	void		*img_ptr;	// pointer to the image struct
	char		*pxl_ptr;	// pointer to the first pixel
	int			bpp;		// how many bits are in pixel
	int			line_len;	// length of one line in bytes
	int			endian;		// marks order of bytes
}				t_img;
*/

typedef struct s_fractol
{
	char		*name;

	void		*mlx;
	void		*mlx_win;

	t_img		img;

	double		edge;
	int			iteration_threshold;
	double		shift_re;
	double		shift_im;
	double		zoom;
}				t_fractol;

// PROTOTYPES
// string utils
int			fractol_strncmp(const char *s1, const char *s2, int n);
int			ft_strlen(const char *str);
int			correct_input(int ac, char *av[]);

// math utils
double		resize(double k, double new_min, double new_max, double old_max);
t_complex	ft_sum_complex(t_complex z, t_complex c);
t_complex	ft_sqr_complex(t_complex z);

// police
void		ft_error_exit(char *error_message);

// fractal render
void		fractal_render(t_fractol *fractal);

// fractal init
void		fractal_init(t_fractol *fractal);

// event_handler
int			ft_key_handler(int keysym, t_fractol *fractal);
int			ft_button_handler(int button, int x, int y, t_fractol *fractal);
int			ft_destroyer(t_fractol *fractal);

#endif