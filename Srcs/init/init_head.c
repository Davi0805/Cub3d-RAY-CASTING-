/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:37:55 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/01/09 21:57:50 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_textures(t_cub *head)
{
    head->assets.no_texture = NULL;
    head->assets.so_texture = NULL;
    head->assets.we_texture = NULL;
    head->assets.ea_texture = NULL;
    head->assets.ceiling_rgb_s = NULL;
    head->assets.floor_rgb_s = NULL;
}

void    init_head(t_cub *head)
{
    init_textures(head);
    head->map_line = 0;
    head->nb_lines = 0;
    head->map_width = 0;
    head->maps = NULL;
}

void    init_minilibx_struct(t_cub *head)
{
    head->mlx.mlx_ptr = NULL;
    head->mlx.win_ptr = NULL;
    head->mlx.img_addr = NULL;
    head->mlx.bits_per_pixel = 0;
    head->mlx.endian = 0;
    head->mlx.size_line = 0;
}
