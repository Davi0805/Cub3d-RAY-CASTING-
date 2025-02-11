/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:04:56 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:44:51 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>
# include <sys/time.h>

// MINILIBX
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "mlx_int.h"

// Libft
# include "libft.h"

# define WIDTH 800
# define HEIGHT 600

# define MOVESPEED 1.2 // tiles per second
# define ROTSPEED 1.2 // radians per second
# define FOV 0.66

// ERROR CODES
# define PARSE_SUCCESS 0
# define PARSE_ERROR 1
# define ARG_ERROR 1
# define FTYPE_ERROR 1
# define FEMPTY_ERROR 1
# define FINVALID_ERROR 1
# define MWRONG_TEXTURE 1
# define MWRONG_FORMAT 1
# define SYSCALL_ERROR 1

// ORIENTATION
enum e_orientation
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4, // Floor
	C = 5, // Ceiling
	OTHER = 100
};

typedef struct s_point
{
	int		x;
	int		y;
}	t_point;

typedef struct s_drawline_helper
{
	void	*texture;
	int		tex_width;
	int		tex_height;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	wall_x;
	int		*texture_data;
	int		size_line;
	double	step;
	int		color;
}	t_davitone;

typedef struct s_dda
{
	// tlvz mudar para float
	int		dx;
	int		dy;
	int		steps;
	float	xinc;
	float	x;
	float	y;
	float	yinc;
}	t_dda;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		hit;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
}	t_ray;

typedef struct rgb
{
	// RGB ranges from 0-255
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct map_assets
{
	//Paths
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;

	void	*no;
	void	*so;
	void	*we;
	void	*ea;

	// Add texture data
	int		no_width;
	int		so_width;
	int		we_width;
	int		ea_width;

	int		no_height;
	int		so_height;
	int		we_height;
	int		ea_height;
	//Color field String
	char	*floor_rgb_s;
	char	*ceiling_rgb_s;
	//Struct cores separadas
	t_rgb	floor_color;
	t_rgb	ceil_color;
}	t_assets;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_mlx_data;

typedef struct s_movement
{
	bool	w_key;
	bool	s_key;
	bool	a_key;
	bool	d_key;
	bool	l_key;
	bool	r_key;
}	t_moves;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	t_moves	moves;
}	t_player;

typedef struct cub
{
	// File validation
	uint32_t		nb_lines; //Number of lines in the file
	char			**fcontent; // Array[][] line by line
	// Player
	t_player		player;
	// Map
	char			**map;
	int				map_height;
	int				*map_l_lens;
	// Texturas
	t_assets		assets;
	// MLX stuff
	t_mlx_data		mlx;
	struct timeval	time;
	double			delta_time;
}	t_cub;

// MAP VALIDATION
uint8_t	filetype_checker(char *path);
uint8_t	is_file_valid(char *path);
uint8_t	is_file_empty(char *path);
uint8_t	is_orientation(t_cub *head, int i, int textures_parsed);
uint8_t	texture_validator(t_cub *head);
uint8_t	is_xpm(char *str);

// MAP INIT
uint8_t	get_nb_lines(char *path, t_cub *head);
int		get_map_height(char *map_path);
bool	is_map_line(char *line);
bool	has_bad_chars(t_cub *head);
void	get_start_dir(t_player *player, char direction);
uint8_t	allocate_file(char **av, t_cub *head);
uint8_t	collect_lines(char *path, t_cub *head);
uint8_t	allocate_map(t_cub *head, char **fcontent, char *map_path);
uint8_t	verify_map(t_cub *head);
uint8_t	is_texture_valid(t_cub *head);
uint8_t	is_color_rgbstring(char *str);

void	texture_loader(t_cub *head);

// Time Utils
double	delta_time(struct timeval *old);

// Player movement
void	player_forward(t_player *player, char **map, t_cub *head);
void	player_backward(t_player *player, char **map, t_cub *head);
void	player_left(t_player *player, char **map, t_cub *head);
void	player_right(t_player *player, char **map, t_cub *head);
void	player_rotate_right(t_cub *head, t_player *player);
void	player_rotate_left(t_cub *head, t_player *player);

// Ray caster
int		raycaster(t_cub *head);

// Draw utils
void	draw_line(t_mlx_data mlx, t_point p1, t_point p2, int color);
void	put_pixel_to_img(t_mlx_data mlx, int x, int y, int color);
void	DrawVertPixelLine(t_cub *head, int color, t_ray *ray, int x);
void	draw_vline_textured(t_cub *head, t_ray *ray, int x);

// hooks
int		key_released(int key, t_cub *head);
int		key_pressed(int key, t_cub *head);
int		update_loop(t_cub *head);

// Free Funcs
void	free_file(t_cub *head);
void	free_textures(t_cub *head);
void	free_map(t_cub *head);
void	parse_failed(t_cub *head, uint16_t error);
int		exit_fun(t_cub *head);

#endif