#include "libft.h"

bool ft_stremptyspaces(char *str)
{
    if (!str)
        return true;
    while (*str)
    {
        if (!ft_isspace(*str))
            return false;
        str++;
    }
    return true;
}