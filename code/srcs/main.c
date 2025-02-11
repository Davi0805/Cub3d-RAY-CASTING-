/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/02/11 20:35:59 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint8_t	setup_validation(int ac, char **av, t_cub *head)
{
	if (ac != 2)
		return (PARSE_ERROR);
	if (filetype_checker(av[1]))
		parse_failed (head, FTYPE_ERROR);
	if (is_file_valid(av[1]))
		parse_failed (head, FINVALID_ERROR);
	if (is_file_empty(av[1]))
		parse_failed (head, FEMPTY_ERROR);
	if (allocate_file(av, head))
		parse_failed (head, PARSE_ERROR);
	if (texture_validator(head))
		parse_failed(head, MWRONG_TEXTURE);
	if (allocate_map(head, head->fcontent, av[1]))
		parse_failed(head, MWRONG_TEXTURE);
	if (verify_map(head))
		parse_failed (head, MWRONG_TEXTURE);
	return (PARSE_SUCCESS);
}

uint8_t	setup_minilibx(t_cub *head)
{
	head->mlx.mlx_ptr = mlx_init();
	if (head->mlx.mlx_ptr == NULL)
		return (PARSE_ERROR);
	head->mlx.win_ptr = mlx_new_window(head->mlx.mlx_ptr, WIDTH, HEIGHT, \
						"CUB3D");
	if (head->mlx.win_ptr == NULL)
		return (PARSE_ERROR);
	head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (head->mlx.img_ptr == NULL)
		return (PARSE_ERROR);
	head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, \
						&head->mlx.bits_per_pixel, &head->mlx.size_line, \
						&head->mlx.endian);
	if (head->mlx.img_addr == NULL)
		return (PARSE_ERROR);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	head;

	ft_bzero(&head, sizeof(head));
	if (setup_validation(ac, av, &head))
		return (1);
	if (setup_minilibx(&head))
		return (1);
	texture_loader(&head);
	gettimeofday(&head.time, NULL);
	mlx_loop_hook(head.mlx.mlx_ptr, update_loop, (void *)&head);
	mlx_hook(head.mlx.win_ptr, KeyPress, KeyPressMask, key_pressed, &head);
	mlx_hook(head.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_released, &head);
	mlx_hook(head.mlx.win_ptr, DestroyNotify, 1L << 0, exit_fun, &head);
	mlx_loop(head.mlx.mlx_ptr);
	exit_fun(&head);
	return (0);
}
