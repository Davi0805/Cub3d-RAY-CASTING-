/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/02/12 10:20:04 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


uint8_t     setup_validation(int ac, char **av, t_cub *head)
{
	if (ac != 2)
		return (PARSE_ERROR);
	
	// File type
	if (filetype_checker(av[1])) parseFailed (head, FTYPE_ERROR);
	// File opens
	if (isFileValid(av[1])) parseFailed (head, FINVALID_ERROR);
	// Has contents
	if (isFileEmpty(av[1])) parseFailed (head, FEMPTY_ERROR);
	
	// Heap storing the file contents into a buffer
	if (allocate_file(av, head)) parseFailed (head, PARSE_ERROR);
	// TEXTURES Validation
	if (textureValidator(head)) parseFailed(head, MWRONG_TEXTURE);

	// Read file contents and allocate map
	if (allocateMap(head, head->fcontent, av[1])) parseFailed(head, MWRONG_TEXTURE);
	// MAP Validation
	if (verifyMap(head)) parseFailed (head, MWRONG_TEXTURE);


	return (PARSE_SUCCESS);
}

uint8_t     setup_minilibx(t_cub *head)
{
	head->mlx.mlx_ptr = mlx_init();
	if (head->mlx.mlx_ptr == NULL)
		return (ft_putstr_fd("Error\n", 2), PARSE_ERROR);
	
	head->mlx.win_ptr = mlx_new_window(head->mlx.mlx_ptr, WIDTH, HEIGHT, "CUB3D - Oq tu quer ta mole");
	if (head->mlx.win_ptr == NULL)
		return (ft_putstr_fd("Error\n", 2), PARSE_ERROR);
	
	head->mlx.img_ptr = mlx_new_image(head->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (head->mlx.img_ptr == NULL)
		return (ft_putstr_fd("Error\n", 2), PARSE_ERROR);
	
	head->mlx.img_addr = mlx_get_data_addr(head->mlx.img_ptr, &head->mlx.bits_per_pixel, &head->mlx.size_line, &head->mlx.endian);
	if (head->mlx.img_addr == NULL)
		return (ft_putstr_fd("Error\n", 2), PARSE_ERROR);

	return (0);
}

int main(int ac, char **av)
{
	t_cub head;

	// Init everything to 0's
	ft_bzero(&head, sizeof(head));
	// Valid file
	if (setup_validation(ac, av, &head))
		return (1);

	if (setup_minilibx(&head))
		return (1);

	texture_loader(&head);
	gettimeofday(&head.time, NULL);

	mlx_loop_hook(head.mlx.mlx_ptr, UpdateLoop, (void *)&head);
	mlx_hook(head.mlx.win_ptr, KeyPress, KeyPressMask, KeyPressed, &head);
	mlx_hook(head.mlx.win_ptr, KeyRelease, KeyReleaseMask, KeyReleased, &head);
	mlx_hook(head.mlx.win_ptr, DestroyNotify, 1L << 0, ExitFun, &head);
	mlx_loop(head.mlx.mlx_ptr);

	// Resource deallocation
	ExitFun(&head);
	return (0);
}