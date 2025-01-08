#include <stdio.h>
#include "cub3d.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    
    if (filetype_checker(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);

    return (0);
}