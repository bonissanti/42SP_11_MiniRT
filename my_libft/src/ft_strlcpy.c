/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:02:04 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function copies a string from src to dst up to a size of size.
*/

#include "../include/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (!dest || !src)
		return (0);
	else if (size <= 0)
		return (ft_strlen(src));
	while (*src && size > 1)
	{
		*dest++ = *src++;
		size--;
	}
	*dest = '\0';
	return (len);
}
