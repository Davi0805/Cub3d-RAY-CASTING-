/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyHandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:59:36 by davi              #+#    #+#             */
/*   Updated: 2025/01/21 17:38:21 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>

void updatePlayerDirection(t_player *player)
{
    if (player->pa > 2 * PI)
        player->pa -= 2 * PI;
    else if (player->pa < 0)
        player->pa += 2 * PI;

    player->pdx = cos(player->pa) * 5;
    player->pdy = sin(player->pa) * 5;
}

int handle_keypress(int keycode, t_cub *head)
{
    if (keycode == XK_Escape) // ESC 
        exitHandler(head);
    if (keycode == XK_s)
    {
        head->player.px -= head->player.pdx;
        head->player.py -= head->player.pdy;

        ft_memset(head->mlx.img_addr, 0, HEIGHT * head->mlx.size_line);
        drawMiniMap(*head);
        draw_player(*head);
        // RAYCASTER
        {
            for (int i = 0; )   


        drawLine(head.mlx, x, y, x + dx, y + dy);
        
        
        }
        
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    }
    if (keycode == XK_w)
    {
        head->player.px += head->player.pdx;
        head->player.py += head->player.pdy;

        ft_memset(head->mlx.img_addr, 0, HEIGHT * head->mlx.size_line);
        drawMiniMap(*head);
        draw_player(*head);
        // RAYCASTER
        {
            for (int i = 0; )   


                drawLine(head.mlx, x, y, x + dx, y + dy);
        
        
        }
        
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    }
    if (keycode == XK_d)
    {
        head->player.pa += (1) * (PI / 180.0);

        updatePlayerDirection(&head->player);

        ft_memset(head->mlx.img_addr, 0, HEIGHT * head->mlx.size_line);
        drawMiniMap(*head);
        draw_player(*head);
        // RAYCASTER
        {
            for (int i = 0; )   


        drawLine(head.mlx, x, y, x + dx, y + dy);
        
        
        }
        
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    }
    if (keycode == XK_a)
    {
        head->player.pa -= (1) * (PI / 180.0);

        updatePlayerDirection(&head->player);
                 
        ft_memset(head->mlx.img_addr, 0, HEIGHT * head->mlx.size_line);
        drawMiniMap(*head);
        draw_player(*head);
        // RAYCASTER
        {


        drawLine(head.mlx, x, y, x + dx, y + dy);
        
        
        }
        
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, head->mlx.img_ptr, 0, 0);
    }
    printf("PlayerX %f\n", head->player.px);
    printf("PlayerY %f\n", head->player.py);
    printf("PlayerDeltaX %f\n", head->player.pdx);
    printf("PlayerDeltaY %f\n", head->player.pdy);
    printf("PlayerAngle %f\n", head->player.pa * 180/PI);
    // TODO Adicionar outras teclas
    return (0);
}

int handle_close(t_cub *head)
{
    exitHandler(head);
    return (0);
}