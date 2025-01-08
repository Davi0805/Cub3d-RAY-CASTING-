/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/01/08 16:21:13 by davi             ###   ########.fr       */
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
    return (0);
}

int main(int ac, char **av)
{
    t_cub head;
    
    if (setup_validation(ac, av, &head) == PARSE_ERROR)
        return (PARSE_ERROR);

    return (0);
}