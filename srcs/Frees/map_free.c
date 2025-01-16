/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:21 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/01/16 17:02:01 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Da free ao mapa inteiro
void    freeFile(t_cub *head)
{
    uint32_t i;

    if (!head->fcontent)
        return ;
    i = 0;
    while (i < head->nb_lines)
    {
        if (head->fcontent[i])
            free(head->fcontent[i]);
        i++;
    }
    if (head->fcontent)
        free(head->fcontent);
}

// Free nas texturas e cores
void    free_textures(t_cub *head)
{
    if (head->assets.no_texture != NULL)
        free(head->assets.no_texture);
    if (head->assets.so_texture != NULL)
        free(head->assets.so_texture);
    if (head->assets.we_texture != NULL)
        free(head->assets.we_texture);
    if (head->assets.ea_texture != NULL)
        free(head->assets.ea_texture);
    if (head->assets.floor_rgb_s != NULL)
        free(head->assets.floor_rgb_s);
    if (head->assets.ceiling_rgb_s)
        free(head->assets.ceiling_rgb_s);
}

void freeMap(t_cub *head)
{
    for (int i = 0; head->map[i]; i++)
        free(head->map[i]); // rows
    free(head->map); // cols
    return ;
}

void    parseFailed(t_cub *head, uint16_t error)
{
    printf("[EXIT HANDLER]\n");
    freeFile(head);
    free_textures(head);
    exit(error); // Macro para Parse Test
}

void    exitHandler(t_cub *head)
{
    printf("[EXIT HANDLER]\n");
    if (head->mlx.img_ptr != NULL)
        mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
    if (head->mlx.win_ptr != NULL)
        mlx_destroy_window(head->mlx.mlx_ptr, head->mlx.win_ptr);
    if (head->mlx.mlx_ptr != NULL)
        mlx_destroy_display(head->mlx.mlx_ptr);
    if (head->mlx.mlx_ptr != NULL)
        free(head->mlx.mlx_ptr);
    freeFile(head);
    free_textures(head);
    freeMap(head);
    exit(0);
}