/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:15:47 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 20:19:54 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Validacao do path das texturas
uint8_t	is_texture_valid(t_cub *head)
{
	if (is_file_valid(head->assets.no_texture) \
		|| is_xpm(head->assets.no_texture))
		return (MWRONG_TEXTURE);
	if (is_file_valid(head->assets.so_texture) \
		|| is_xpm(head->assets.so_texture))
		return (MWRONG_TEXTURE);
	if (is_file_valid(head->assets.we_texture) \
		|| is_xpm(head->assets.we_texture))
		return (MWRONG_TEXTURE);
	if (is_file_valid(head->assets.ea_texture) \
		|| is_xpm(head->assets.ea_texture))
		return (MWRONG_TEXTURE);
	return (PARSE_SUCCESS);
}

static bool	is_valid_channel_end(char c, uint32_t channel)
{
	if (c == ',' && channel < 2)
		return (true);
	if (c == '\0' && channel == 2)
		return (true);
	return (false);
}

static uint8_t	validate_channel(char *str, uint32_t *i, uint32_t channel)
{
	uint32_t	nb_per_channel;

	nb_per_channel = 0;
	while (ft_isspace(str[*i]))
		(*i)++;
	while (str[*i] != ',' && str[*i] != '\0')
	{
		if (!ft_isdigit(str[*i]))
			return (MWRONG_TEXTURE);
		nb_per_channel++;
		(*i)++;
	}
	if ((nb_per_channel == 0 && channel != 0) || nb_per_channel > 3)
		return (MWRONG_TEXTURE);
	if (!is_valid_channel_end(str[*i], channel))
		return (MWRONG_TEXTURE);
	if (str[*i] == ',')
		(*i)++;
	return (PARSE_SUCCESS);
}

uint8_t	is_color_rgbstring(char *str)
{
	uint32_t	i;
	uint32_t	channel;
	uint8_t		status;

	if (str == NULL)
		return (PARSE_ERROR);
	i = 0;
	channel = 0;
	while (channel < 3)
	{
		status = validate_channel(str, &i, channel);
		if (status != PARSE_SUCCESS)
			return (status);
		channel++;
	}
	return (PARSE_SUCCESS);
}
