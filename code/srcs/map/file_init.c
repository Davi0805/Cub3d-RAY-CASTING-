/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:44 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 16:44:37 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Preenche head->fcontent
uint8_t collect_lines(char *path, t_cub *head)
{
    int32_t fd;
    uint32_t i;

    i = 0;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (SYSCALL_ERROR);
    
    while(i < head->nb_lines)
    {
        head->fcontent[i] = get_next_line(fd);
        if (!head->fcontent[i]) return (close(fd), SYSCALL_ERROR);
        i++;
    }
    close(fd);
    return (PARSE_SUCCESS);
}

uint8_t allocate_file(char ** av, t_cub *head)
{
    if (getNbLines(av[1], head)) return (SYSCALL_ERROR);

    head->fcontent = ft_calloc(head->nb_lines, sizeof(char *));
    if (!head->fcontent)
        return (SYSCALL_ERROR);

    if (collect_lines(av[1], head)) return (freeFile(head), SYSCALL_ERROR);    
    return (0);
}
