/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:27:06 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This code allocates memory for a string, copies the string into 
the allocated memory, and returns a pointer to the copied string. */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*p;
	int		len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	str = malloc(len + 1);
	if (str == NULL)
	{
		return (NULL);
	}
	p = str;
	while (*s != '\0')
	{
		*p = *s;
		p++;
		s++;
	}
	*p = '\0';
	return (str);
}
