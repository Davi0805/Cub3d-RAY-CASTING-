/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:28:21 by dmelo-ca          #+#    #+#             */
/*   Updated: 2025/01/09 16:14:17 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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