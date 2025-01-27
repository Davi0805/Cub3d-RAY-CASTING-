/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:20:35 by artuda-s          #+#    #+#             */
/*   Updated: 2025/01/27 18:22:46 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	DeltaTime(struct timeval *old)
{
	struct timeval	new;
	double			delta_time;

	gettimeofday(&new, NULL);
	delta_time = (new.tv_sec - old->tv_sec) + \
				(new.tv_usec - old->tv_usec) * 1e-6;
	if (delta_time <= 0)
		return (1 / 120);
	else
		return (delta_time);
}
