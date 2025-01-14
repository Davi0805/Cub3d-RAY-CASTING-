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

uint8_t isMapclosed(t_cub *head)
{
    uint8_t valid;
    
    (void)head;    
    valid = 1;
    printf("[IsMapClosed] Entrando\n");
    printf("FLOOD FILLED LELELELELLELE\n");

    if (valid == 0)
        return (PARSE_ERROR);
    return (0);
}