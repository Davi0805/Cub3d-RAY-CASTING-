/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:28:42 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 16:45:19 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint8_t    getNbLines(char *path, t_cub *head)
{
    int32_t fd;
    uint32_t nb_lines;
    char *str;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (PARSE_ERROR);
    
    nb_lines = 0;
    str = get_next_line(fd);
    while(str != NULL)
    {    
        nb_lines++;
        free(str);
        str = get_next_line(fd);
    }    
    head->nb_lines = nb_lines;
    close(fd);
    return (0);
}

char *getTexturePath(char *line)
{
    uint32_t i;
    uint32_t size;
    char *str;
    
    //F 20,20,20
    //C 200,200,200
    i = 2;
    str = "";
    size = ft_strlen(line) - 1;
    while(line[i] == ' ' || line[i] == '\t')
        i++;
    while(line[size] == ' ' || line[size] == '\t')
    {
        size--;
    }
    str = ft_substr(line, i, size - i + 1);
    free(line);
    printf("[getTexturePath]: %s\n", str);
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
    if (ft_strncmp(line, "NO", 2) == 0)
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

    if (i <= 4)
        return (PARSE_ERROR);
    
    if (ft_strncmp(str + i, ".xpm", 4) == 0)
    {
        //printf("[IS_XPM]: YES");
        return (0);
    }
    return (PARSE_ERROR);
}

void getMapWidth(t_cub *head)
{
    uint32_t i;
    uint32_t size;

    i = head->map_line;
    size = 0;
    while(i < head->nb_lines)
    {
        if (ft_strlen(head->maps[i]) > head->map_width)
            size = ft_strlen(head->maps[i]);
        i++;
    }
    head->map_width = size;
    printf("[MAP WIDTH]%d\n", head->map_width);
}