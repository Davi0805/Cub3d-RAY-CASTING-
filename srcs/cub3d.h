#ifndef CUB3D_HPP
#define CUB3D_HPP

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

// MINILIBX
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

// Libft
#include "libft.h"

#define WIDTH 1920
#define HEIGHT 1080

// GAME CONFIGS
#define SPEED 35
#define SCALE 50

// RADIANOS
#define PI 3.1415926535

// ERROR CODES
#define PARSE_ERROR 1
//TODO
#define PARSE_SUCCESS 0
#define ARG_ERROR 1
#define FTYPE_ERROR 1
#define FEMPTY_ERROR 1
#define FINVALID_ERROR 1
#define MWRONG_TEXTURE 1
#define MWRONG_FORMAT 1

#define SYSCALL_ERROR 1

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

// Variaveis para calculo do dda
typedef struct s_dda
{
    // tlvz mudar para float
    int dx;
    int dy;
    int steps;
    float xinc;
    float x;
    float y;
    float yinc;
}               t_dda;

typedef struct s_player
{
    float px;
    float py;
    float pdx; // delta x
    float pdy; // delta y
    float pa; // angulo do player
    int8_t  start_dir;

} t_player;


typedef struct cub
{
    // File validation
    uint32_t nb_lines; //Number of lines in the file
    char **fcontent; // Array[][] line by line

    // Player
    t_player player;

    // Map
    char **map;

    // Texturas
    t_assets assets;
    
    // MLX stuff
    t_mlx_data mlx;
}       t_cub;


// MAP VALIDATION
uint8_t filetype_checker(char *path);
uint8_t isFileValid(char *path);
uint8_t isFileEmpty(char *path);
uint8_t isOrientation(t_cub *head, int i, int textures_parsed);
uint8_t textureValidator(t_cub *head);
uint8_t isXpm(char *str);

// MAP INIT
uint8_t getNbLines(char *path, t_cub *head);
uint8_t allocate_file(char ** av, t_cub *head);
uint8_t collect_lines(char *path, t_cub *head);

uint8_t allocateMap(t_cub *head, char **fcontent, char *map_path);
uint8_t verifyMap(t_cub *head);

// Variable initializer
void init_head(t_cub *head);
// void    init_minilibx_struct(t_cub *head);

// Key Hooks
int handle_keypress(int keycode, t_cub *head);
int handle_close(t_cub *head);

// Free Funcs
void freeFile(t_cub *head);
void free_textures(t_cub *head);
void freeMap(t_cub *head);

// DDA
void    drawLine(t_mlx_data mlx, int x1, int y1, int x2, int y2);
void	put_pixel(t_mlx_data mlx, int x, int y, int color);
void    draw_square(t_mlx_data mlx, int x, int y, int size, int color);
void drawMiniMap(t_cub head);
void draw_player(t_cub head);

void exitHandler(t_cub *head);
void parseFailed(t_cub *head, uint16_t error);

#endif