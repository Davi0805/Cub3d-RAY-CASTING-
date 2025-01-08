/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:31 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 21:59:57 by davi             ###   ########.fr       */
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
    if (isFileValid(head->assets.no_texture) || isXpm(head->assets.no_texture))
    {
        printf("[NAO VALIDADO]: NO TEXTURE\n");
        return (PARSE_ERROR);
    }
    if (isFileValid(head->assets.so_texture) || isXpm(head->assets.so_texture))
    {
        printf("[NAO VALIDADO]: SO TEXTURE\n");
        return (PARSE_ERROR);
    }
    if (isFileValid(head->assets.we_texture) || isXpm(head->assets.we_texture))
    {
        printf("[NAO VALIDADO]: WE TEXTURE\n");
        return (PARSE_ERROR);
    }
    if (isFileValid(head->assets.ea_texture) || isXpm(head->assets.ea_texture))
    {
        printf("[NAO VALIDADO]: EA TEXTURE\n");
        //printf("EA PATH: %s\n", head->assets.ea_texture); // Debug print
        return (PARSE_ERROR);
    }
    printf("[TEXTURAS VALIDADAS]\n");
    return (0);
}

uint8_t isColorRgbstring(char *str)
{
    uint32_t i;
    uint32_t channel; // 3 espectros/canais r g b
    uint32_t nb_per_channel;

    channel = 0;
    nb_per_channel = 0;
    i = 0;
    if (str == NULL)
        return (PARSE_ERROR);
    while (channel < 3)
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        while (str[i] != ',' && str[i] != '\0')
        {
            if (str[i] < '0' || str[i] > '9')
                return (PARSE_ERROR);
            if (str[i] >= '0' && str[i] <= '9')
                nb_per_channel++;
            i++;
        }
        if (nb_per_channel == 0 || nb_per_channel > 3)
            return (PARSE_ERROR);
        if (str[i] == ',')
        {
            nb_per_channel = 0;
            channel++;
            i++;
        }
        else if (str[i] == '\0' && channel == 2)
        {
            channel++;
        }
        else
        {
            return (PARSE_ERROR);
        }
    }
    printf("[IS COLOR VALID]: YES\n");
    return (0);
}

uint8_t isColorValid(t_cub *head)
{
    printf("[ISCOLORVALID] ENTRANDO!\n");
    if(isColorRgbstring(head->assets.floor_rgb_s) == PARSE_ERROR
    || isColorRgbstring(head->assets.ceiling_rgb_s) == PARSE_ERROR)
        return (PARSE_ERROR);

    head->assets.floor_color.r = ft_atoi(head->assets.floor_rgb_s); // Vai parar na primeira virgula
    head->assets.floor_color.g = ft_atoi(ft_strchr(head->assets.floor_rgb_s, ',') + 1);
    head->assets.floor_color.b = ft_atoi(ft_strrchr(head->assets.floor_rgb_s, ',') + 1);

    head->assets.ceil_color.r = ft_atoi(head->assets.ceiling_rgb_s); // Vai parar na primeira virgula
    head->assets.ceil_color.g = ft_atoi(ft_strchr(head->assets.ceiling_rgb_s, ',') + 1); // Retorna primeira virgula e adiciono mais 1
    head->assets.ceil_color.b = ft_atoi(ft_strrchr(head->assets.ceiling_rgb_s, ',') + 1); // Retorno a utlima virgula e adiciono mais 1
    
    printf("[ISCOLORVALID] INT FLOOR COLORS %u %u %u\n", head->assets.floor_color.r, head->assets.floor_color.g, head->assets.floor_color.b);
    printf("[ISCOLORVALID] INT Ceiling COLORS %u %u %u\n", head->assets.ceil_color.r, head->assets.ceil_color.g, head->assets.ceil_color.b);
    printf("[ISCOLORVALID] Sucesso em ambos!\n");
    return (0);
}

uint8_t textureValidator(t_cub *head)
{
    uint8_t i;
    uint8_t orient; // macro retornada

    head->textures_parsed = 0;
    i = -1;
    while (++i < head->nb_lines && head->textures_parsed != 6)
    {
        orient = isOrientation(head->maps[i], head);
        /* printf("[%d] %s", i, head->maps[i]); */
        if (orient != PARSE_ERROR)
        {
            head->textures_parsed++;
        }
    }
    if (head->textures_parsed == 6)
    {
        printf("[NO PATH]: %s\n", head->assets.no_texture);
        printf("[SO PATH]: %s\n", head->assets.so_texture);
        printf("[WE PATH]: %s\n", head->assets.we_texture);
        printf("[EA PATH]: %s\n", head->assets.ea_texture);
        printf("[FLOOR COLOR STRING]: %s\n", head->assets.floor_rgb_s);
        printf("[Ceiling COLOR STRING]: %s\n", head->assets.ceiling_rgb_s);
        if (isTextureValid(head) == PARSE_ERROR)
            return (PARSE_ERROR);
        if (isColorValid(head) == PARSE_ERROR)
            return (PARSE_ERROR);
        printf("PASSOU\n");
        return (0);
    }
    return (PARSE_ERROR);
}
