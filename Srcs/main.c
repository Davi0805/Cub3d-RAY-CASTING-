/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 17:54:57 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

uint8_t     setup_validation(int ac, char **av, t_cub *head)
{
    if (ac != 2)
        return (PARSE_ERROR);
    
    // IF ELSES MERAMENTE ILUSTRATIVOS POIS DEPOIS A SAIDA SERA FEITA NA MINILIBX
    
    if (filetype_checker(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);
    if (isFileValid(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);
    if (isFileEmpty(av[1]) == PARSE_ERROR)
        return (PARSE_ERROR);
    getNbLines(av[1], head);
    if (allocate_map(head) == PARSE_ERROR)
        return (PARSE_ERROR);
    collect_lines(av[1], head);
    if (textureValidator(head) == PARSE_ERROR)
        return (PARSE_ERROR);
    if (isCharInMap(head, '1') == PARSE_ERROR)
        return (PARSE_ERROR);
    if (isTherePlayer(head) == PARSE_ERROR)
        return (PARSE_ERROR);
    getPlayerPos(head);
    /* if (isMapclosed(head) == PARSE_ERROR)
        return (PARSE_ERROR); */
    return (0);
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


uint8_t     setup_minilibx(t_cub *head)
{
    init_minilibx_struct(head);
    head->mlx.mlx_ptr = mlx_init();
    if (head->mlx.mlx_ptr == NULL)
        printf("[MINILIBX]: Falha no setup!");
    head->mlx.win_ptr = mlx_new_window(head->mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D - Oq tu quer ta mole");
    if (head->mlx.win_ptr == NULL)
        printf("[MINILIBX]: Falha no setup!");
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    if (head->mlx.img_ptr == NULL)
        printf("[MINILIBX]: Falha no setup!");
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
    if (head->mlx.img_addr == NULL)
        printf("[MINILIBX]: Falha no setup!");

    return (0);
}

int main(int ac, char **av)
{
    t_cub head;
    
    init_head(&head);
    if (setup_validation(ac, av, &head) == PARSE_ERROR)
        return (PARSE_ERROR);
    setup_minilibx(&head);
    mlx_loop(head.mlx.mlx_ptr);
    free_map(&head);
    free_textures(&head);
    return (0);
}