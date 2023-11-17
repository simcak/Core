/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:25:08 by psimcak           #+#    #+#             */
/*   Updated: 2023/11/17 20:22:02 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include <stdio.h> // printf
#include <stdlib.h> // malloc free
#include <unistd.h> // write, constands
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define ERROR_MESSAGE \
"Please enter: \t\"./fractol mandelbrot\" \n\t\tOR \
\n\t\t\"./fractol julia <value_1> <value_2>\"\n"

// WINDOW SIZE
#define WIDTH	900
#define HEIGHT	900

// COLORS
// basic ones
#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)
// cool ones
#define DEEP_SPACE_SPARKLE	0x4A646C
#define ELECTRIC_BLUE		0x7DF9FF
#define NEON_GREEN			0x39FF14
#define ELECTRIC_PURPLE		0xBF00FF
#define CYBER_GRAPE			0x58427C
#define TURQUOISE_BLUE		0x00FFEF
#define PHTHALO_BLUE		0x000F89
#define HOT_MAGENTA			0xFF1DCE
#define NEON_FUCHSIA		0xFE4164
#define OUTRAGEOUS_ORANGE	0xFF6E4A

// STRUCTURES
typedef struct	s_complex
{
	double	Re;
	double	Im;
}				t_complex;

typedef struct	s_fractol
{
	
}				t_fractol;

// PROTOTYPES
// utils
int	fractol_strncmp(const char *s1, const char *s2, int n);
int	ft_strlen(const char *str);

#endif