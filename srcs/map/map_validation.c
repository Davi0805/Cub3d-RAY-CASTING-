/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:31 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 16:42:56 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Ends in .cub?
uint8_t filetype_checker(char *path)
{
    uint32_t i;

    i = ft_strlen(path);
    if(i <= 4)
        return (FTYPE_ERROR);
    
    // *.cub
    i = i - 4;
    if (ft_strncmp(path + i, ".cub", 4) != 0)
        return (FTYPE_ERROR);

    return (PARSE_SUCCESS);
}
// Verifica se arquivo existe pelo fd retornado
uint8_t isFileValid(char *path)
{
    int32_t fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (FINVALID_ERROR);
    close(fd);
    return (PARSE_SUCCESS);
}
// Verifica se o arquivo esta vazio
uint8_t isFileEmpty(char *path)
{
    int32_t fd;
    uint8_t has_content;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (FEMPTY_ERROR);
    
    // Trying to read 1 byte from the file
    if (read(fd, &has_content, 1) == 0)
        return (FEMPTY_ERROR);

    close(fd);
    return (PARSE_SUCCESS);
}

// Validacao do path das texturas
uint8_t isTextureValid(t_cub *head) //todo printfs
{
    if (isFileValid(head->assets.no_texture) || isXpm(head->assets.no_texture))
    {
        printf("[NAO VALIDADO]: NO %s\n", strerror(errno));
        return (MWRONG_TEXTURE);
    }
    if (isFileValid(head->assets.so_texture) || isXpm(head->assets.so_texture))
    {
        printf("[NAO VALIDADO]: SO %s\n", strerror(errno));
        return (MWRONG_TEXTURE);
    }
    if (isFileValid(head->assets.we_texture) || isXpm(head->assets.we_texture))
    {
        printf("[NAO VALIDADO]: WE %s\n", strerror(errno));
        return (MWRONG_TEXTURE);
    }
    if (isFileValid(head->assets.ea_texture) || isXpm(head->assets.ea_texture))
    {
        printf("[NAO VALIDADO]: EA %s\n", strerror(errno));
        //printf("EA PATH: %s\n", head->assets.ea_texture); // Debug print
        return (MWRONG_TEXTURE);
    }
    printf("[TEXTURAS VALIDADAS]\n");
    return (PARSE_SUCCESS);
}

// Validar RGB em formato de string
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
        if ((nb_per_channel == 0 && channel != 0) || nb_per_channel > 3) //O Primeiro canal pode ser vazio se possuir virgula
            return (PARSE_ERROR);
        if (str[i] == ',')
        {
            nb_per_channel = 0;
            channel++;
            i++;
        }
        else if (str[i] == '\0' && channel == 2)
            channel++;
        else
            return (PARSE_ERROR);
    }
    printf("[IS COLOR VALID]: YES\n");
    return (0);
}

// Parser func de RGB
uint8_t isColorValid(t_cub *head)
{
    // t_rgb *fcolor = &(head->assets.floor_color);
    // t_rgb *ccolor = &(head->assets.ceil_color.r);

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
// Da parse e valida Texturas e cores
uint8_t textureValidator(t_cub *head)
{
    uint8_t i;

    i = 0;
    while (i < head->nb_lines && head->textures_parsed != 6)
    {
        errno = 0;
        if(isOrientation(&head->fcontent[i], head) != OTHER)
        {
            if (errno != 0)
                return (SYSCALL_ERROR);
            head->textures_parsed++;
        }
        i++;
    }

    // All need to be present
    if (head->textures_parsed != 6)
        return (MWRONG_TEXTURE);

    //? DEBUGGING
    {
        printf("[NO PATH]: %s#\n", head->assets.no_texture);
        printf("[SO PATH]: %s#\n", head->assets.so_texture);
        printf("[WE PATH]: %s#\n", head->assets.we_texture);
        printf("[EA PATH]: %s#\n", head->assets.ea_texture);
        printf("[FLOOR COLOR STRING]: %s\n", head->assets.floor_rgb_s);
        printf("[Ceiling COLOR STRING]: %s\n", head->assets.ceiling_rgb_s);
    }
    
    if (isTextureValid(head)) return (MWRONG_TEXTURE);
    if (isColorValid(head) == PARSE_ERROR)
        return (PARSE_ERROR);
    head->map_line = i + 2;
    getMapWidth(head);
    printf("PASSOU\n");
    return (0);
}
// Procurar char no mapa
// Usado para validar Personagem e paredes
uint8_t isCharInMap(t_cub *head, char c)
{
    uint32_t i;
    uint32_t j;

    i = head->map_line;
    while (i < head->nb_lines)
    {
        j = -1;
        while(head->fcontent[i][++j] != '\0')
        {
            if (head->fcontent[i][j] == c)
                return (0);
        }
        i++;
    }
    printf("[IsMap]: Erro no MAPA\n");
    return (PARSE_ERROR);
}

// is handling player invalid cases unless player multiple
uint8_t isTherePlayer(t_cub *head)
{
    uint32_t i;
    uint32_t j;
    uint32_t p_found;

    p_found = 0;
    i = head->map_line;
    while (i < head->nb_lines)
    {
        j = -1;
        while(head->fcontent[i][++j] != '\0')
        {          
            if (ft_strchr("WNSE", (int)head->fcontent[i][j]))
                p_found++;
        }
        i++;
    }
    if (p_found == 1)
        return (0);
    printf("[IsMap]: Erro no MAPA\n");
    return (PARSE_ERROR);
}

// Player pos getter
void getPlayerPos(t_cub *head)
{
    uint32_t i;

    i = head->map_line;
    while (i < head->nb_lines)
    {
        if (ft_strchr(head->fcontent[i], 'W'))
        {
            head->player.py= i;
            if (ft_strchr(head->fcontent[i], 'W') > head->fcontent[i])
                head->player.px = ft_strchr(head->fcontent[i], 'W') - head->fcontent[i];
            else
                head->player.px = -1;
        }
        else if (ft_strchr(head->fcontent[i], 'N'))
        {
            head->player.py= i;
            if (ft_strchr(head->fcontent[i], 'W') > head->fcontent[i])
                head->player.px = ft_strchr(head->fcontent[i], 'W') - head->fcontent[i];
            else
                head->player.px = -1;
        }
        else if( ft_strchr(head->fcontent[i], 'S'))
        {
            head->player.py= i;
            if (ft_strchr(head->fcontent[i], 'W') > head->fcontent[i])
                head->player.px = ft_strchr(head->fcontent[i], 'W') - head->fcontent[i];
            else
                head->player.px = -1;
        }
        else if (ft_strchr(head->fcontent[i], 'E'))
        {
            head->player.py= i;
            if (ft_strchr(head->fcontent[i], 'W') > head->fcontent[i])
                head->player.px = ft_strchr(head->fcontent[i], 'W') - head->fcontent[i];
            else
                head->player.px = -1;
        }
        i++;
    }
    printf("[PLAYER POS] y = %d | x = %d\n", head->player.py, head->player.px);
}