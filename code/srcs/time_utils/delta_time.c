/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:20:35 by artuda-s          #+#    #+#             */
/*   Updated: 2025/02/11 18:40:31 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	delta_time(struct timeval *old)
{
	struct timeval	new;
	double			dt;

	gettimeofday(&new, NULL);
	dt = (new.tv_sec - old->tv_sec) + \
				(new.tv_usec - old->tv_usec) * 1e-6;
	if (dt <= 0)
		return (1 / 120);
	else
		return (dt);
}
