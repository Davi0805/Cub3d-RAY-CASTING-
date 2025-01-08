#include <stdio.h>
#include "cub3d.h"

uint8_t     setup_validation(int ac, char **av)
{
    if (ac != 2)
        return (PARSE_ERROR);

    if (filetype_checker(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);
    if (isFileValid(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);
    if (isFileEmpty(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);
    return (0);
}

int main(int ac, char **av)
{
    if (setup_validation(ac, av) == PARSE_ERROR)
        return (PARSE_ERROR);

    return (0);
}