#include "cub3d.h"

static bool checkCharacters(t_cub *head)
{
    char **map = head->map;

    bool hasPlayer = false;
    int x = 0, y = 0;
    while (map[y]) // ultimo é NULL
    {
        x = 0;
        while (map[y][x] != '\n' || map[y][x] != '\0') // \n ou EOF
        {
            if (ft_strchr("NSEW", map[y][x])) // bad char
            {
                if (hasPlayer)
                    return true;
                head->player.start_dir = map[y][x]; // fetch starting dir
                hasPlayer = true;
            }
            else if (!ft_strchr("01", map[y][x])) // bad char
                return true;
            x++;
        }
        y++;
    }
    return false; // all good
}

// static bool mapNotClosed(t_cub *head)
// {
    
// }

uint8_t verifyMap(t_cub *head)
{
    // Checks for invalid charcaters and 1 player only
    if (checkCharacters(head)) return (MWRONG_FORMAT);
    // Checks for closed map with flood fill
    if (mapNotClosed(head)) return (MWRONG_FORMAT);

    return (PARSE_SUCCESS);
}