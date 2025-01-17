#include "cub3d.h"

static bool hasBadChars(t_cub *head)
{
    char **map = head->map;

    bool hasPlayer = false;
    int x = 0, y = 0;
    while (map[y]) // ultimo é NULL
    {
        x = 0;
        while (map[y][x] != '\n' && map[y][x] != '\0') // \n ou EOF
        {
            if (ft_strchr("NSEW", map[y][x])) // bad char
            {
                if (hasPlayer)
                    return true;
                head->player.start_dir = map[y][x]; // fetch starting dir
                head->player.px = x; // fetch starting px
                head->player.py = y; // fetch starting py

                hasPlayer = true;
            }
            else if (!ft_strchr("01 ", map[y][x])) // bad char
                return true;
            x++;
        }
        y++;
    }
    return hasPlayer ? false : true;
}

bool floodFill(char **map, int y, int x, char to_fill)
{
    if (x < 0 || y < 0 || map[y] == NULL || (map[y][x] == '\n' || map[y][x] == '\0'))
        return true; // if out of bounds === map not closed

    if (map[y][x] != to_fill && !ft_strchr("NSEW", map[y][x])) // wall
        return false;
    
    map[y][x] = 'x'; // 0s in the map will become F!!!

    bool edge = false;
    edge |= floodFill(map, y, x - 1, to_fill);
    edge |= floodFill(map, y, x + 1, to_fill);
    edge |= floodFill(map, y - 1, x, to_fill);
    edge |= floodFill(map, y + 1, x, to_fill);
    return edge;
}

static bool mapNotClosed(t_cub *head)
{
    return (floodFill(head->map, head->player.py, head->player.px, '0'));
}

uint8_t verifyMap(t_cub *head)
{
    // Checks for invalid charcaters and 1 player only
    if (hasBadChars(head)) return (MWRONG_FORMAT);

    // Checks for closed map with flood fill
    if (mapNotClosed(head))
        return (MWRONG_FORMAT);

    return (PARSE_SUCCESS);
}