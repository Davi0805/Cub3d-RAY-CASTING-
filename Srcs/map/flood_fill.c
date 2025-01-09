/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:10:59 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 02:17:05 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    flood_fill(t_cub *head, int32_t pX, int32_t pY, uint8_t *valid)
{
    char **map;
    
    map = head->maps;
    // Limites
    if(pX < 0 || pY < 0 || !map[pY][pX] || !map[pY] || head->player_pos_x == -1)
    {
        *valid = 0;
        return ;
    }
   /* if(pX < 0 || pY < head->map_line || head->player_pos_x == -1)
    {
        *valid = 0;
        return ;
    } */
    
    if (map[pY][pX] == '1' || map[pY][pX] == 'V')
        return;

    if (map[pY][pX] == ' ')
    {
        *valid = 0;
        return ;
    }
    
    map[pY][pX] = 'V';

    // Nao entendi ainda mas aparenta ir em todas as direcoes recursivamente
    flood_fill(head, pX + 1, pY, valid);
    flood_fill(head, pX - 1, pY, valid);
    flood_fill(head, pX, pY + 1, valid);
    flood_fill(head, pX, pY - 1, valid); 
}

uint8_t isMapclosed(t_cub *head)
{
    uint8_t valid;
    
    valid = 1;
    printf("[IsMapClosed] Entrando\n");
    flood_fill(head, head->player_pos_x, head->player_pos_y, &valid);

    if (valid == 0)
        return (PARSE_ERROR);
    return (0);
}