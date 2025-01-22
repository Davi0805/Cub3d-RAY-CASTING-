/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:37:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/23 21:02:01 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	n;

	if (!s || !*s)
		return ;
	n = ft_strlen(s);
	write(fd, s, n);
}
/*
#include <stdio.h>

int	main(void)
{
	ft_putstr_fd("ola\n", 1);
	return (0);
} */