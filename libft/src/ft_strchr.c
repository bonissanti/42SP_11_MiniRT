/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:37:08 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_strchr finds the first occurrence of c in s
// s is the string to search
// c is the character to find
// returns a pointer to the first occurrence of c in s
// returns NULL if c is not found

#include "../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	c_ascii;

	c_ascii = c;
	while (*str != '\0')
	{
		if (*str == c_ascii)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c_ascii == '\0')
		return ((char *)str);
	return (NULL);
}
