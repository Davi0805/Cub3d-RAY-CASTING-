/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:28:42 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 15:46:24 by davi             ###   ########.fr       */
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