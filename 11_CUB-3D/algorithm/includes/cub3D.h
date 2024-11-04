/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/04 09:48:34 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/********************************** Macros ********************************** */

/********************************** Libraries **********************************
 * errno.h	-	Error handling = errno
 * math.h	-	Mathematical functions
 * fcntl.h	-	File control options = O_RDONLY, open
 * unistd.h	-	Standard symbolic constants and types = read, write, close
 * stdio.h	-	Standard input/output = printf, perror
 * stdlib.h	-	Standard library definitions = malloc, free, exit, +_SUCCESS,
 * 				+_FAILURE
 * string.h	-	String operations = strerror
 * stdbool.h-	Boolean type and values = bool, true, false
 */
# include "../../MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

/* ********************************** Color ********************************* */
# define BR						"\033[1;31m"
# define RST					"\033[0m"

/* ********************************** Init ********************************** */
# define DEFAULT				0
# define GAME					1
# define MLX					2

/* ********************************* Debug ********************************** */
# define ALL					0

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

/* ****************************** Error messages **************************** */
# define ERR_MALL_MAP			BR"Memory allocation failed for map"RST
# define ERR_MALL_GAME			BR"Memory allocation failed for game"RST

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
	int				fd;
	char			**parsed_file;
	char			**grid;
	int				width;
	int				height;
	int				start_count;
	int				start_x;
	int				start_y;
	char			start_dir;
	char			*tx_no;
	char			*tx_so;
	char			*tx_we;
	char			*tx_ea;
	mlx_texture_t	*mlx_tx_no;
	mlx_texture_t	*mlx_tx_so;
	mlx_texture_t	*mlx_tx_we;
	mlx_texture_t	*mlx_tx_ea;
	
}	t_map;

typedef struct s_main
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*animation;
	mlx_texture_t	*animation_txt;

	t_player		*player;
	t_ray			*ray;
	t_map			*map;
}	t_main;

/* ******************************* Prototypes ******************************* */
// Utils
void	ft_debug(int type, t_main *game);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	safe_exit(t_main *game, const char *msg);
void	safe_free(t_main *game);
void	*ft_safe_malloc(size_t size, char *msg);

// Init
void	init_default(t_main *game);
void	init(int type, t_main *game, int ac, char **av);

// Parser
void	parser(t_main *game);

#endif