/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeEverything.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:30:31 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:38:44 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Da free ao mapa inteiro
void	free_file(t_cub *head)
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

void	free_map(t_cub *head)
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

void	parse_failed(t_cub *head, uint16_t error)
{
	free_file(head);
	if (head->map)
		free_map(head);
	free_textures(head);
	if (head->map_l_lens)
		free(head->map_l_lens);
	exit(error);
}

// Frees everything and exits
int	exit_fun(t_cub *head)
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
	free_file(head);
	free_textures(head);
	if (head->map)
		free_map(head);
	if (head->map_l_lens)
		free(head->map_l_lens);
	exit(0);
}
