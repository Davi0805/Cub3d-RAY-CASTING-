#ifndef CUB3D_HPP
#define CUB3D_HPP

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// MINILIBX
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

// Libft
#include "libft.h"

#define WIDTH 1920
#define HEIGHT 1080

// ERROR CODES
#define PARSE_ERROR 1
//TODO
#define PARSE_SUCCESS 0
#define ARG_ERROR 1
#define FTYPE_ERROR 2
#define FEMPTY_ERROR 3
#define FINVALID_ERROR 4
#define MWRONG_TEXTURE 5
#define MWRONG_FORMAT 6
#define MNO_PLAYER 7

#define SYSCALL_ERROR 8

// ORIENTATION
enum orientation
{
NO = 1,
SO = 2,
WE = 3,
EA = 4,
F = 5, // Floor
C = 6, // Ceiling
OTHER = 100
};

typedef struct rgb
{
    // RGB ranges from 0-255
    uint8_t r;
    uint8_t g;
    uint8_t b;
}               t_rgb;

typedef struct map_assets
{
    //Paths
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;

    //Color field String
    char *floor_rgb_s;
    char *ceiling_rgb_s;

    //Struct cores separadas
    t_rgb floor_color;
    t_rgb ceil_color;
}               t_assets;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx_data;

typedef struct s_player
{
    int32_t px;
    int32_t py;
    int8_t  start_dir;

} t_player;


typedef struct cub
{
    // File validation
    uint32_t nb_lines; //Number of lines in the file
    char **fcontent; // Array[][] line by line

    uint32_t map_line; //? Index do mapa OU apenas depois dos Assets
    uint32_t map_width; //? is this really needed
    uint8_t textures_parsed; //? Index de Assets carregados
   
    // Player
    t_player player;

    // Texturas
    t_assets assets;
    
    // MLX stuff
    t_mlx_data mlx;
}       t_cub;


// MAP VALIDATION
uint8_t filetype_checker(char *path);
uint8_t isFileValid(char *path);
uint8_t isFileEmpty(char *path);
uint8_t isOrientation(char *line, t_cub *head);
uint8_t textureValidator(t_cub *head);
uint8_t isXpm(char *str);
uint8_t isCharInMap(t_cub *head, char c);
void getMapWidth(t_cub *head);
void getPlayerPos(t_cub *head);
uint8_t isMapclosed(t_cub *head);
uint8_t isTherePlayer(t_cub *head);

// MAP INIT
uint8_t getNbLines(char *path, t_cub *head);
uint8_t allocate_file(char ** av, t_cub *head);
uint8_t collect_lines(char *path, t_cub *head);

// Variable initializer
void    init_head(t_cub *head);
// void    init_minilibx_struct(t_cub *head);

// Key Hooks
int handle_keypress(int keycode, t_cub *head);
int handle_close(t_cub *head);

// Free Funcs
void    free_map(t_cub *head);
void    free_textures(t_cub *head);
void    exitHandler(t_cub *head);
void    parseFailed(t_cub *head, uint16_t error);

#endif