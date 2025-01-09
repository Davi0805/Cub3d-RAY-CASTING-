/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:37:55 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/01/09 16:06:01 by dmelo-ca         ###   ########.fr       */
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
