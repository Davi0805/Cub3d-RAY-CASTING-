/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:44 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 15:48:04 by davi             ###   ########.fr       */
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
        printf("[%u] %s", i, head->maps[i]);
        i++;
    }
    return (0);
}