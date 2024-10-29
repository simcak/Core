/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/10/29 15:57:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/********************************** Macros ********************************** */

/********************************** Libraries **********************************
 * math.h	-	Mathematical functions
 * fcntl.h	-	File control options = O_RDONLY, open
 * unistd.h	-	Standard symbolic constants and types = read, write, close
 * stdio.h	-	Standard input/output = printf, perror
 * stdlib.h	-	Standard library definitions = malloc, free, exit, +_SUCCESS,
 * 				+_FAILURE
 * string.h	-	String operations = strerror
 */
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* ********************************* Screen ********************************* */
# define SCREEN_HEIGHT			1000
# define SCREEN_WIDTH			1500
# define FOV					60
# define ROTATION_SPEED			0.05
# define MOVE_SPEED				5

/* ********************************* Texture ******************************** */
# define TEXTURE_HEIGHT			64
# define TEXTURE_WIDTH			64

/* ****************************** Game controls ***************************** */
# define ESC					53
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_EXIT			17

/* ***************************** Player controls **************************** */
# define W						13
# define A						0
# define S						1
# define D						2
# define UP						126
# define DOWN					125
# define LEFT					123
# define RIGHT					124

/* ******************************* Structure ******************************** */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	float	fov_rad;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
}	t_ray;

typedef struct s_map
{
	char	**map;
	double	width;
	double	height;
}	t_map;

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	t_player	*player;
	t_ray		*rays;
	t_map		*map;
}	t_mlx;

#endif