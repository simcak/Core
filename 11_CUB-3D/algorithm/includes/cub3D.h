/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/11/21 14:58:38 by psimcak          ###   ########.fr       */
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
# define BR					"\033[1;31m"
# define BG					"\033[1;32m"
# define BY					"\033[1;33m"
# define BB					"\033[1;34m"
# define BW					"\033[1;37m"
# define BM					"\033[1;35m"
# define RST				"\033[0m"

/* ********************************** Error ********************************* */
#define ERR_MAP_NOT_FOUND	BR"No valid map found in provided file."RST
#define ERR_MALL_CLR		BR"Malloc failed for 2D color setup"RST
#define ERR_MALL_RGB		BR"Malloc failed for 2D rgb setup"RST
#define ERR_RGB				BR"RGB values must be digits in range 0-255\n\
Format: e.c. '255,5,42' or '255  ,5,   42 '"RST
#define ERR_RGB_COUNT		BR"There must be ONE number <0-255> per color"RST
#define ERR_MGRID			BR"Couldn't allocate memory for 'grid'"RST
#define ERR_WALL			BR"The map must be closed/surrounded by walls from "
/* ********************************** Init ********************************** */
# define DEFAULT			0
# define GAME				1
# define MLX				2

/* ********************************* Debug ********************************** */
# define ALL				0

/* ********************************* Screen ********************************* */
# define SCREEN_HEIGHT		1000
# define SCREEN_WIDTH		1500
# define FOV				60
# define ROTATION_SPEED		0.05
# define MOVE_SPEED			5

/* ********************************* Texture ******************************** */
# define TEXTURE_HEIGHT		64
# define TEXTURE_WIDTH		64

/* ****************************** Game controls ***************************** */
# define ESC				53
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RLS	3
# define X_EVENT_EXIT		17

/* ***************************** Player controls **************************** */
# define W					13
# define A					0
# define S					1
# define D					2
# define UP					126
# define DOWN				125
# define LEFT				123
# define RIGHT				124

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
	char			**txt_paths;
	char			**colors;
	char			**rgb_raw;
	int				*rgb_c;
	int				*rgb_f;
	char			**grid;
	int				width;
	int				height;
	int				start_count;
	int				start_x;
	int				start_y;
	char			start_dir;
	mlx_texture_t	*mlx_txt_no;
	mlx_texture_t	*mlx_txt_so;
	mlx_texture_t	*mlx_txt_we;
	mlx_texture_t	*mlx_txt_ea;
	
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
int		ft_atoi(const char *original_str);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_get_next_line(int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	safe_exit(t_main *game, const char *msg);
void	free_full(t_main *game);
int		free_str_arr(char **arr);
void	*ft_dalloc(size_t size, int n, char *msg);
void	*ft_smalloc(size_t size, char *msg);
bool	is_space(char c);
bool	is_digit(char c);
int		space_counter(char *input);
void	are_spaces_or_digits(t_main *game, char *rgb);
bool	line_has_only_spaces(char *line);
int		last_char_index(char *str);

// Init
void	init_default(t_main *game);
void	init(int type, t_main *game, int ac, char **av);

// Parser
void	range_check(t_main *game, int rgb);
void	difference_check(t_main *game, int *rgb_c, int *rgb_f);
void	parse_load_check_colors(t_main *game);
void	parse_load_check_file(t_main *game);
void	parser(t_main *game);
void	parse_load_check_map(t_main *game);
void	parse_load_check_texture(t_main *game);
bool	we_found_flag(t_main *game, char *flag, int line);
char	*txt_path_finder(t_main *game, char *flag, int line);
void	ft_dupliempty_txtp(t_main *game, char **txt_paths);

#endif