/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyHandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi <davi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:59:36 by davi              #+#    #+#             */
/*   Updated: 2025/01/09 22:01:04 by davi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>

int handle_keypress(int keycode, t_cub *head)
{
    if (keycode == XK_Escape) // ESC 
        exitHandler(head);
    // TODO Adicionar outras teclas
    return (0);
}

int handle_close(t_cub *head)
{
    exitHandler(head);
    return (0);
}