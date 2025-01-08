/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:31 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 17:42:32 by davi             ###   ########.fr       */
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

uint8_t isTextureValid(t_cub *head)
{
    if (isFileValid(head->assets.no_texture))
    {
        printf("[NAO VALIDADO]: NO TEXTURE\n");
        return (PARSE_ERROR);
    }
    if (isFileValid(head->assets.so_texture))
    {
        printf("[NAO VALIDADO]: SO TEXTURE\n");
        return (PARSE_ERROR);
    }
    if (isFileValid(head->assets.we_texture))
    {
        printf("[NAO VALIDADO]: WE TEXTURE\n");
        return (PARSE_ERROR);
    }
    if (isFileValid(head->assets.ea_texture))
    {
        printf("[NAO VALIDADO]: EA TEXTURE\n");
        //printf("EA PATH: %s\n", head->assets.ea_texture); // Debug print
        return (PARSE_ERROR);
    }
    printf("[TEXTURAS VALIDADAS]\n");
    return (0);
}

uint8_t textureValidator(t_cub *head)
{
    uint8_t i;
    uint8_t orient; // macro retornada

    head->textures_parsed = 0;
    i = -1;
    while (++i < head->nb_lines && head->textures_parsed != 4)
    {
        orient = isOrientation(head->maps[i], head);
        /* printf("[%d] %s", i, head->maps[i]); */
        if (orient != PARSE_ERROR)
        {
            head->textures_parsed++;
        }
    }
    if (head->textures_parsed == 4)
    {
        printf("[NO PATH]: %s\n", head->assets.no_texture);
        printf("[SO PATH]: %s\n", head->assets.so_texture);
        printf("[WE PATH]: %s\n", head->assets.we_texture);
        printf("[EA PATH]: %s\n", head->assets.ea_texture);
        if (isTextureValid(head) == PARSE_ERROR)
            return (PARSE_ERROR);
        printf("PASSOU\n");
        return (0);
    }
    return (PARSE_ERROR);
}