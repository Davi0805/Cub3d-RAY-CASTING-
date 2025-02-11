/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeEverything.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/11 15:58:16 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// Da free ao mapa inteiro
void	freeFile(t_cub *head)
{
	uint32_t	i;

	if (!head->fcontent)
		return ;
	i = 0;
	while (i < head->nb_lines)
	{
		if (head->fcontent[i])
			free(head->fcontent[i]);
		i++;
	}
	if (head->fcontent)
		free(head->fcontent);
}

// Free nas texturas e cores
void	free_textures(t_cub *head)
{
	if (head->assets.no_texture != NULL)
		free(head->assets.no_texture);
	if (head->assets.so_texture != NULL)
		free(head->assets.so_texture);
	if (head->assets.we_texture != NULL)
		free(head->assets.we_texture);
	if (head->assets.ea_texture != NULL)
		free(head->assets.ea_texture);
	if (head->assets.floor_rgb_s != NULL)
		free(head->assets.floor_rgb_s);
	if (head->assets.ceiling_rgb_s != NULL)
		free(head->assets.ceiling_rgb_s);
}

void	freeMap(t_cub *head)
{
	int	i;

	i = 0;
	while (head->map[i])
	{
		free(head->map[i]);
		i++;
	}
	free(head->map);
	return ;
}

void	parseFailed(t_cub *head, uint16_t error)
{
	freeFile(head);
	if (head->map)
		freeMap(head);
	free_textures(head);
	exit(error);
}

// Frees everything and exits
int	ExitFun(t_cub *head)
{
    mlx_destroy_image(head->mlx.mlx_ptr, (void *)head->assets.no);
    mlx_destroy_image(head->mlx.mlx_ptr, (void *)head->assets.so);
    mlx_destroy_image(head->mlx.mlx_ptr, (void *)head->assets.we);
    mlx_destroy_image(head->mlx.mlx_ptr, (void *)head->assets.ea);
	if (head->mlx.img_ptr != NULL)
		mlx_destroy_image(head->mlx.mlx_ptr, head->mlx.img_ptr);
	if (head->mlx.win_ptr != NULL)
		mlx_destroy_window(head->mlx.mlx_ptr, head->mlx.win_ptr);
	if (head->mlx.mlx_ptr != NULL)
		mlx_destroy_display(head->mlx.mlx_ptr);
	if (head->mlx.mlx_ptr != NULL)
		free(head->mlx.mlx_ptr);
	freeFile(head);
    free_textures(head);
	if (head->map)
		freeMap(head);
	if (head->mapLineLens)
		free(head->mapLineLens);
	exit(0);
}
