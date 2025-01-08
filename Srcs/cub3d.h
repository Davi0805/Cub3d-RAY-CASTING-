#ifndef CUB3D_HPP
#define CUB3D_HPP

#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define PARSE_ERROR 1

/* // Exemplos de uso:
uint8_t  u8  = 255;       // Representante natural: unsigned char
uint16_t u16 = 65535;     // Representante natural: unsigned short
uint32_t u32 = 4294967295U; // Representante natural: unsigned int
uint64_t u64 = 18446744073709551615ULL; // Representante natural: unsigned long long

int8_t   i8  = -128;      // Representante natural: signed char
int16_t  i16 = -32768;    // Representante natural: short
int32_t  i32 = -2147483648; // Representante natural: int
int64_t  i64 = -9223372036854775807LL; // Representante natural: long lon */

// MAP VALIDATION
uint8_t filetype_checker(char *path);
uint8_t isFileValid(char *path);
uint8_t isFileEmpty(char *path);

#endif // !CUB3D_HPP