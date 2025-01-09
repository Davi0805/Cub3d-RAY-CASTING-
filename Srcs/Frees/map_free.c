/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:21 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/01/09 22:13:16 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Da free ao mapa inteiro
void    free_map(t_cub *head)
{
    uint32_t i;

    i = -1;
    while (++i < head->nb_lines)
    {
        free(head->maps[i]);
    }
    free(head->maps);
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

void    parseFailed(t_cub *head)
{
    printf("[EXIT HANDLER]\n");
    free_map(head);
    free_textures(head);
    exit(PARSE_ERROR); // Macro para Parse Test
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
    free_map(head);
    free_textures(head);
    exit(0);
}