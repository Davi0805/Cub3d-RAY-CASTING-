/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:28:42 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 16:19:58 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint8_t    getNbLines(char *path, t_cub *head)
{
    int32_t fd;
    uint32_t nb_lines;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (PARSE_ERROR);
    
    nb_lines = 0;
    while(get_next_line(fd) != NULL)
        nb_lines++;
    head->nb_lines = nb_lines;
    close(fd);
    return (0);
}

uint8_t     isOrientation(char *line)
{
    uint32_t i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (ft_strncmp((line + i), "NO", 2) == 0)
        return (NO);
    else if (ft_strncmp((line + i), "SO", 2) == 0)
        return (SO);
    else if (ft_strncmp((line + i), "WE", 2) == 0)
        return (WE);
    else if (ft_strncmp((line + i), "EA", 2) == 0)
        return (EA);
    else
        return (PARSE_ERROR);
}