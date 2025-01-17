/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/01/17 15:50:10 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>

uint8_t     setup_validation(int ac, char **av, t_cub *head)
{
    if (ac != 2)
        return (PARSE_ERROR);
    
    if (isFileValid(av[1])) parseFailed (head, FINVALID_ERROR); //! check
    if (filetype_checker(av[1])) parseFailed (head, FTYPE_ERROR); //! check
    if (isFileEmpty(av[1])) parseFailed (head, FEMPTY_ERROR); //! check
    if (allocate_file(av, head)) parseFailed (head, PARSE_ERROR); //! check
    if (textureValidator(head)) parseFailed(head, MWRONG_TEXTURE); //!check

    // MAP FETCH
    // Read file contents and allocate map
    if (allocateMap(head, head->fcontent, av[1])) parseFailed(head, MWRONG_TEXTURE); //! check
    // MAP Validation
    if (verifyMap(head)) parseFailed (head, MWRONG_TEXTURE);
    // 1 e 1 só player
    // nao ha letras no meio
    // mapa fechado (flood fill)

    // if (isCharInMap(head, '1')) parseFailed(head, MWRONG_FORMAT);
    // if (isTherePlayer(head)) parseFailed(head, MNO_PLAYER);
    
    // getPlayerPos(head);
    
    return (0);
}


uint8_t     setup_minilibx(t_cub *head)
{
    // init_minilibx_struct(head);
    
    head->mlx.mlx_ptr = mlx_init();
    if (head->mlx.mlx_ptr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);
    
    head->mlx.win_ptr = mlx_new_window(head->mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D - Oq tu quer ta mole");
    if (head->mlx.win_ptr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);
    
    head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
    if (head->mlx.img_ptr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);
    
    head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
    if (head->mlx.img_addr == NULL)
        return (printf("[MINILIBX]: Falha no setup!"), PARSE_ERROR);

    return (0);
}


int main(int ac, char **av)
{
    t_cub head;
    int error;
    
    ft_bzero(&head, sizeof(head));

    // Valid file
    error = setup_validation(ac, av, &head);
    
    if (error) 
        return (error);
    
    if (setup_minilibx(&head))
        exitHandler(&head);
        
    // drawLine(head.mlx, 2, 2, 255, 255);

    // multiplicado player pos por escala
    head.player.px *= SCALE;
    head.player.py *= SCALE;

    head.player.pdx = cos(head.player.pa);
    head.player.pdy = sin(head.player.pa);

    
    drawMiniMap(head);
    draw_player(head);
    mlx_put_image_to_window(head.mlx.mlx_ptr, head.mlx.win_ptr, head.mlx.img_ptr, 0, 0);
    
    mlx_hook(head.mlx.win_ptr, KeyPress, KeyPressMask, handle_keypress, &head); // ESC
    mlx_hook(head.mlx.win_ptr, ClientMessage, StructureNotifyMask, handle_close, &head);  // X da janela

    mlx_loop(head.mlx.mlx_ptr);

    freeMap(&head);
    freeFile(&head);
    free_textures(&head);
    return (0);
}