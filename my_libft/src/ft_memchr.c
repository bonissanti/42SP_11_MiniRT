/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:00:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function finds the first occurrence of the character chr in the string
** str, looking byte by byte and returning a pointer to the first occurrence of  
** that character. If the character is not found, then the function returns NULL.
*/

#include "../include/libft.h"

void	*ft_memchr(const void *str, int chr, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)str == (unsigned char)chr)
		{
			return ((unsigned char *)str);
		}
		str++;
		n--;
	}
	return (0);
}
