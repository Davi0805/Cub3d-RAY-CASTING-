/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyHandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:59:36 by davi              #+#    #+#             */
/*   Updated: 2025/01/17 15:46:47 by davi             ###   ########.fr       */
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

    player->pdx = cos(player->pa) * SPEED;
    player->pdy = sin(player->pa) * SPEED;
}

int handle_keypress(int keycode, t_cub *head)
{
    if (keycode == XK_Escape) // ESC 
        exitHandler(head);
    if (keycode == XK_s)
    {
        head->player.px -= head->player.pdx;
        head->player.py -= head->player.pdy;

        mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
        void *newImg = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
        head->mlx.img_ptr = newImg;
        drawMiniMap(*head);
        draw_player(*head);
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, newImg, 0, 0);
    }
    if (keycode == XK_w)
    {
        head->player.px += head->player.pdx;
        head->player.py += head->player.pdy;

        mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
        void *newImg = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
        head->mlx.img_ptr = newImg;
        drawMiniMap(*head);
        draw_player(*head);
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, newImg, 0, 0);
    }
    if (keycode == XK_d)
    {
        head->player.pa += 0.1;

        updatePlayerDirection(&head->player);

        mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
        void *newImg = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
        head->mlx.img_ptr = newImg;
        drawMiniMap(*head);
        draw_player(*head);
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, newImg, 0, 0);
    }
        if (keycode == XK_a)
    {
        head->player.pa -= 0.1;


        updatePlayerDirection(&head->player);
                 
        mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
        void *newImg = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
        head->mlx.img_ptr = newImg;
        drawMiniMap(*head);
        draw_player(*head);
        mlx_put_image_to_window(head->mlx.mlx_ptr, head->mlx.win_ptr, newImg, 0, 0);
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