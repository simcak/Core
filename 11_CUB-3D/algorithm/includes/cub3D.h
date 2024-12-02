/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:53:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/12/02 11:10:52 by psimcak          ###   ########.fr       */
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

/* *********************************** Pi *********************************** */
# define PI_FT				3.141592653589793238462643383279502884197169
# define PI05_FT			1.570796326794896619231321691639751442098584

/* ********************************** Color ********************************* */
# define BR					"\033[1;31m"
# define BG					"\033[1;32m"
# define BY					"\033[1;33m"
# define BB					"\033[1;34m"
# define BW					"\033[1;37m"
# define BM					"\033[1;35m"
# define RST				"\033[0m"

# define BLACK				0x000000FF
# define WHITE				0xFFFFFFFF
# define RED				0xFF0000FF

/* ********************************** Error ********************************* */
#define ERR_MALL			BR"Memory allocation failed for "
#define ERR_MALL_2D			BR"2D malloc failed for "
#define ERR_WALL			BR"The map must be closed/surrounded by walls from "
#define ERR_MAP_NOT_FOUND	BR"No valid map found in provided file."RST
#define ERR_RGB				BR"RGB values must be digits in range 0-255\n\
Format: e.c. '255,5,42' or '255  ,5,   42 '"RST
#define ERR_RGB_COUNT		BR"There must be ONE number <0-255> per color"RST
/* ********************************** Init ********************************** */
# define DEFAULT			1
# define FILE				2
# define PLAYER				3
# define MLX				4

/* ********************************* Debug ********************************** */
# define ALL				0
# define MAP				1
# define MAXI_MAP			2

/* ********************************* Screen ********************************* */
# define SWIDTH				1501
# define SHEIGHT			1001
# define FOV				130
# define ROTATION_SPEED		0.05
# define MOVE_SPEED			4.2
# define TILE_SIZE			89
# define MAXI_GRID			10
# define MINI_MAP_WIDTH		SWIDTH / 4.2
# define MINI_MAP_HEIGHT	SHEIGHT / 4.2
# define PLAYER_COLOR		0xFF0000FF
# define VOID_COLOR			0x000000FF
# define WALL_COLOR			0xFFFFFFFF

/* ******************************* Structure ******************************** */
// in file
typedef struct s_txt
{
	char			**paths;
	mlx_texture_t	*mlx_txt_no;
	mlx_texture_t	*mlx_txt_so;
	mlx_texture_t	*mlx_txt_we;
	mlx_texture_t	*mlx_txt_ea;
}	t_txt;

typedef struct s_color
{
	char			**colors;
	char			**rgb_raw;
	int				*rgb_c;
	int				*rgb_f;
	uint32_t		c_color;
	uint32_t		f_color;
}	t_color;

// in map
typedef struct s_coord_map
{
	int				x;
	int				y;
	char			nswe;
}	t_coord_map;

typedef struct s_map
{
	char			**grid;
	char			**grid_max;
	int				width;
	int				height;
	t_coord_map		start_pos;
}	t_map;

// in main
typedef struct s_file
{
	int				fd;
	char			**parsed_file;

	t_txt			*txt;
	t_color			*color;
	t_map			*map;
}	t_file;

// in player
typedef struct s_vect
{
	double			x;
	double			y;
	double			rad;
}	t_vect;

typedef struct s_player
{
	double			fov_rad;
	t_vect			pos;
	t_vect			nxt_pos;
	t_vect			dir;
	t_vect			plane;
	t_vect			move;
	double			rot_speed;
	double			buff_dist;		// distance to the wall
	double			aspect_ratio;
}	t_player;

typedef struct s_hit
{
	double			x;
	double			y;
}	t_hit;

typedef struct s_ray
{
	double			angle;
	double			angle_diff;
	double			distance;
	double			x_step;
	double			y_step;
	uint32_t		color;
	t_hit			hhit;
	t_hit			vhit;
	t_hit			hit;
}	t_ray;

typedef struct s_wall
{
	double			height;
	double			start;
	double			end;
	double			buff;
}	t_wall;

typedef struct s_main
{
	int				ac;
	char			**av;
	mlx_t			*mlx;
	mlx_image_t		*image;

	t_file			*file;
	t_player		*player;
	t_ray			*ray;
	t_wall			*wall;
}	t_main;

typedef struct s_minimap
{
	int				x;
	int				y;
	int				px;
	int				py;
	uint32_t		color;
	int				pgx;
	int				pgy;
	int				start_x;
	int				start_y;
	int				grid_x;
	int				grid_y;
}	t_minimap;

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
void	**ft_dalloc(t_main *game, size_t size, int rows, char *msg);
void	*ft_smalloc(size_t size, char *msg);
bool	is_space(char c);
bool	is_digit(char c);
int		space_counter(char *input);
void	are_spaces_or_digits(t_main *game, char *rgb);
bool	line_has_only_spaces(char *line);
int		last_char_index(char *str);
bool	is_nswe(char c);
void	ft_replace_chars(char **line, char c1, char c2);
bool	can_step_in(t_map *map, int y, int x);

// Init
void	init(int type, t_main *game);
void	init_default(t_main *game);

// Parser
void	range_check(t_main *game, int rgb);
void	difference_check(t_main *game, int *rgb_c, int *rgb_f);
void	parse_load_check_colors(t_main *game, t_color *color);
void	parse_load_check_file(t_main *game);
void	parser(t_main *game);
void	parse_load_check_map(t_main *game);
void	parse_load_check_texture(t_main *game, t_txt *txt);
bool	we_found_flag(t_main *game, char *flag, int line);
char	*txt_path_finder(t_main *game, char *flag, int line);
void	ft_dupliempty_txtp(t_main *game, char **txt_paths);

// Raycasting
void	ray_cast(t_main *game, t_player *player, t_ray *ray);
double	keep_in_range(double angle);
void	calculate_vertical_hit(t_main *game, t_player *player, t_ray *ray);
void	calculate_horizontal_hit(t_main *game, t_player *player, t_ray *ray);
void	draw_ray(t_main *game, int ray_counter);
void	put_mini_map(t_main *game);
bool	key_down_crossroad(t_main *game);

#endif