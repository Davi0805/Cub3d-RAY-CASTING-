#ifndef CUB3D_HPP
#define CUB3D_HPP

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// MINILIBX
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

// Libft
#include "libft.h"

#define WIDTH 1920
#define HEIGHT 1080

// CODES
#define PARSE_ERROR 1

// ORIENTATION
#define NO 2
#define SO 3
#define WE 4
#define EA 5
#define F 6 // Floor
#define C 7 // Ceiling


/* 
Exemplos de uso:
uint8_t  u8  = 255;       // Representante natural: unsigned char
uint16_t u16 = 65535;     // Representante natural: unsigned short
uint32_t u32 = 4294967295U; // Representante natural: unsigned int
uint64_t u64 = 18446744073709551615ULL; // Representante natural: unsigned long long

int8_t   i8  = -128;      // Representante natural: signed char
int16_t  i16 = -32768;    // Representante natural: short
int32_t  i32 = -2147483648; // Representante natural: int
int64_t  i64 = -9223372036854775807LL; // Representante natural: long lon
*/

typedef struct rgb
{
    uint8_t r; // Cada canal rgb vai apenas ate 255
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

typedef struct cub
{
    uint32_t nb_lines; //Number of lines in the configs and maps
    uint32_t map_line; // Index do mapa OU apenas depois dos Assets
    uint32_t map_width;
    int32_t player_pos_y;
    int32_t player_pos_x;
    uint8_t textures_parsed; //Index de Assets carregados
    char *path;
    char **maps; // Array line by line
    t_assets assets; // Texturas
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
uint8_t allocate_map(t_cub *head);
uint8_t collect_lines(char *path, t_cub *head);

// Variable initializer
void    init_head(t_cub *head);
void    init_minilibx_struct(t_cub *head);

// Key Hooks
int handle_keypress(int keycode, t_cub *head);
int handle_close(t_cub *head);

// Free Funcs
void    free_map(t_cub *head);
void    free_textures(t_cub *head);
void    exitHandler(t_cub *head);
void    parseFailed(t_cub *head);

#endif