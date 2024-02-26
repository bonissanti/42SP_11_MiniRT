/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:28:48 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strjoin() concatenates two 
strings s1 and s2, allocating memory for the new string. 
If the allocation fails, the function returns NULL.
*/

#include "../include/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	p = str;
	while (*s1)
	{
		*p++ = *s1++;
	}
	while (*s2)
	{
		*p++ = *s2++;
	}
	*p = '\0';
	return (str);
}
