/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:44 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 16:44:37 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint8_t allocate_map(t_cub *head)
{
    head->maps = (char **)malloc(sizeof(char *) * head->nb_lines);
    
    if (!head->maps)
        return (PARSE_ERROR);
    return (0);
}
// Preenche head->maps
uint8_t collect_lines(char *path, t_cub *head)
{
    int32_t fd;
    uint32_t i;

    i = 0;
    head->path = path;
    fd = open(head->path, O_RDONLY);
    if (fd == -1)
        return (PARSE_ERROR);
    
    while(i < head->nb_lines)
    {
        head->maps[i] = get_next_line(fd);
        /* printf("[%u] %s", i, head->maps[i]); */
        i++;
    }
    return (0);
}

// Player pos getter
void getPlayerPos(t_cub *head)
{
    uint32_t i;

    i = head->map_line;
    while (i < head->nb_lines)
    {
        if (ft_strchr(head->maps[i], 'W'))
        {
            head->player.py= i;
            if (ft_strchr(head->maps[i], 'W') > head->maps[i])
                head->player.px = ft_strchr(head->maps[i], 'W') - head->maps[i];
            else
                head->player.px = -1;
        }
        else if (ft_strchr(head->maps[i], 'N'))
        {
            head->player.py= i;
            if (ft_strchr(head->maps[i], 'W') > head->maps[i])
                head->player.px = ft_strchr(head->maps[i], 'W') - head->maps[i];
            else
                head->player.px = -1;
        }
        else if( ft_strchr(head->maps[i], 'S'))
        {
            head->player.py= i;
            if (ft_strchr(head->maps[i], 'W') > head->maps[i])
                head->player.px = ft_strchr(head->maps[i], 'W') - head->maps[i];
            else
                head->player.px = -1;
        }
        else if (ft_strchr(head->maps[i], 'E'))
        {
            head->player.py= i;
            if (ft_strchr(head->maps[i], 'W') > head->maps[i])
                head->player.px = ft_strchr(head->maps[i], 'W') - head->maps[i];
            else
                head->player.px = -1;
        }
        i++;
    }
    printf("[PLAYER POS] y = %d | x = %d\n", head->player.py, head->player.px);
}