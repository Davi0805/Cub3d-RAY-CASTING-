/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:28:42 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 20:32:05 by davi             ###   ########.fr       */
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

char *getTexturePath(char *line)
{
    uint32_t i;
    char *str;

    i = 3;
    while(line[i] == ' ' || line[i] == '\t')
        i++;
    str = ft_substr(line, i, ft_strlen(line));
    return (str);
}

void    setTexture(t_cub *head, uint8_t orient, char *path)
{
    if (orient == NO)
    {
        head->assets.no_texture = path;
        return ;
    }
    else if (orient == SO)
    {
        head->assets.so_texture = path;
        return ;
    }
    else if (orient == WE)
    {
        head->assets.we_texture = path;
        return ;
    }
    else if (orient == EA)
    {
        head->assets.ea_texture = path;
        return ;
    }
    return ;   
}

void    setColor(t_cub *head, uint8_t orient, char *path)
{
    if (orient == F)
    {
        head->assets.floor_rgb_s = path;
    }
    else if(orient == C)
    {
        head->assets.ceiling_rgb_s = path;
    }
}

char *trimTabSpace(char *str)
{
    uint32_t i;
    int32_t j; // Limite
    char *trimmed;

    i = 0;
    j = ft_strlen(str) - 1;
    if (j <= 0)
        return (NULL);
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    while (str[j] == ' ' || str[j] == '\t')
        j--;
    
    trimmed = ft_substr(str, i, j - i);
    //printf("[TRIM]: %s\n", trimmed);
    return (trimmed);
}

uint8_t     isOrientation(char *line, t_cub *head)
{
    if (head->textures_parsed == 6)
        return (PARSE_ERROR); // Nao se trata de erro porem estou usando mesmo macro para parar de dar trim
    line = trimTabSpace(line);
    if (line == NULL)
        return (PARSE_ERROR);
    else if (ft_strncmp(line, "NO", 2) == 0)
        return (setTexture(head, NO, getTexturePath(line)), NO);
    else if (ft_strncmp(line, "SO", 2) == 0)
        return (setTexture(head, SO, getTexturePath(line)), SO);
    else if (ft_strncmp(line, "WE", 2) == 0)
        return (setTexture(head, WE, getTexturePath(line)), WE);
    else if (ft_strncmp(line, "EA", 2) == 0)
        return (setTexture(head, EA, getTexturePath(line)), EA);
    else if (ft_strncmp(line, "F", 1) == 0)
        return (setColor(head, F, getTexturePath(line)), F);
    else if (ft_strncmp(line, "C", 1) == 0)
        return(setColor(head, C, getTexturePath(line)), C);
    else
        return (PARSE_ERROR);
}

uint8_t isXpm(char *str)
{
    uint32_t i;

    //printf("[IS_XPM]: %s\n", str);
    i = ft_strlen(str) - 4;
    
    if (ft_strncmp(str + i, ".xpm", 4) == 0)
    {
        //printf("[IS_XPM]: YES");
        return (0);
    }
    return (PARSE_ERROR);
}