/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:08:14 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:09:00 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint8_t	get_nb_lines(char *path, t_cub *head)
{
	int32_t	fd;
	char	*str;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (SYSCALL_ERROR);
	head->nb_lines = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		head->nb_lines++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (PARSE_SUCCESS);
}

uint8_t	is_xpm(char *str)
{
	uint32_t	i;

	i = ft_strlen(str) - 4;
	if (i <= 4)
		return (MWRONG_TEXTURE);
	if (ft_strncmp(str + i, ".xpm", 4) == 0)
		return (PARSE_SUCCESS);
	return (MWRONG_TEXTURE);
}
