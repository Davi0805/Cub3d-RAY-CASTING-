/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:44 by davi              #+#    #+#             */
/*   Updated: 2025/02/12 10:18:22 by artuda-s         ###   ########.fr       */
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
    head->assets.no = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.no_texture, &head->assets.no_width, &head->assets.no_height);
    head->assets.so = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.so_texture, &head->assets.so_width, &head->assets.so_height);
    head->assets.we = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.we_texture, &head->assets.we_width, &head->assets.we_height);
    head->assets.ea = mlx_xpm_file_to_image(head->mlx.mlx_ptr, head->assets.ea_texture, &head->assets.ea_width, &head->assets.ea_height);
    if (!head->assets.no || !head->assets.so || !head->assets.we || !head->assets.ea)
    {
        ft_putstr_fd("Error\n", 2);
        ExitFun(head);
    }
}
