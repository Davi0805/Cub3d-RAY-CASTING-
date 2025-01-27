/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:07 by artuda-s          #+#    #+#             */
/*   Updated: 2025/01/27 17:22:29 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Recieves a writtable string and trims it's spaces at the end
// Returns a new trimmed pointer to the start of the string and places
// a null byte at the end of the trimmed string
char	*ft_trim(char *str)
{
	char	*end;

	if (!str || !*str)
		return (NULL);
	while (*str == ' ')
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;
	end[1] = '\0';
	return (str);
}
