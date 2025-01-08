#ifndef CUB3D_HPP
#define CUB3D_HPP

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "libft.h"

// CODES
#define PARSE_ERROR 1

// ORIENTATION
#define NO 2
#define SO 3
#define WE 4
#define EA 5
#define F 6 // Floor color
#define C 7 // Ceiling color


/* // Exemplos de uso:
uint8_t  u8  = 255;       // Representante natural: unsigned char
uint16_t u16 = 65535;     // Representante natural: unsigned short
uint32_t u32 = 4294967295U; // Representante natural: unsigned int
uint64_t u64 = 18446744073709551615ULL; // Representante natural: unsigned long long

int8_t   i8  = -128;      // Representante natural: signed char
int16_t  i16 = -32768;    // Representante natural: short
int32_t  i32 = -2147483648; // Representante natural: int
int64_t  i64 = -9223372036854775807LL; // Representante natural: long lon */

typedef struct rgb
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
}               t_rgb;


typedef struct map_assets
{
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *floor_rgb_s;
    char *ceiling_rgb_s;
    t_rgb floor_color;
    t_rgb ceil_color;
}               t_assets;

typedef struct cub
{
    uint32_t nb_lines;
    uint32_t map_line;
    uint8_t textures_parsed;
    char *path;
    char **maps; // Array line by line
    t_assets assets; // Texturas
}       t_cub;


// MAP VALIDATION
uint8_t filetype_checker(char *path);
uint8_t isFileValid(char *path);
uint8_t isFileEmpty(char *path);
uint8_t     isOrientation(char *line, t_cub *head);
uint8_t textureValidator(t_cub *head);
uint8_t isXpm(char *str);
uint8_t isMap(t_cub *head);

// MAP INIT
uint8_t    getNbLines(char *path, t_cub *head);
uint8_t allocate_map(t_cub *head);
uint8_t collect_lines(char *path, t_cub *head);

#endif