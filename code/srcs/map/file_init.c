/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:44 by davi              #+#    #+#             */
/*   Updated: 2025/01/28 13:06:14 by dmelo-ca         ###   ########.fr       */
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

void texture_loader(t_cub *head)
{
    printf("[TEXUTRES]: NO - %s | SO - %s | WE - %s | EA - %s\n", head->assets.no_texture, head->assets.so_texture, head->assets.we_texture, head->assets.ea_texture);

    int size[1];

    size[0] = 64;

    head->assets.no = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.no_texture, &size[0], &size[0]);
    head->assets.so = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.so_texture, &size[0], &size[0]);
    head->assets.we = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.we_texture, &size[0], &size[0]);
    head->assets.ea = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.ea_texture, &size[0], &size[0]);
}
