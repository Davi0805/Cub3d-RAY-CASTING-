/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:31 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 15:11:34 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint8_t filetype_checker(char *path)
{
    uint32_t i;

    i = ft_strlen(path);

    if(i <= 4)
        return (PARSE_ERROR);

    i = i - 4;
    if (ft_strncmp(path + i, ".cub", 4) != 0)
        return (PARSE_ERROR);

    return 0;
}

uint8_t isFileValid(char *path)
{
    int32_t fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (PARSE_ERROR);
    close(fd);
    return (0);
}

uint8_t isFileEmpty(char *path)
{
    int32_t fd;
    uint8_t buffer[1];
    uint32_t nb_read;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (PARSE_ERROR);
    
    nb_read = read(fd, buffer, 1);

    if (nb_read == 0)
        return (PARSE_ERROR);

    close(fd);
    return (0);
}