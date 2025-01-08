#include "../cub3d.h"

uint8_t filetype_checker(char *path)
{
    uint32_t i;

    i = strlen(path);

    if(i <= 4)
        return (PARSE_ERROR);

    i = i - 4;
    if (strncmp(path + i, ".cub", 4) != 0)
        return (PARSE_ERROR);

    return 0;
}