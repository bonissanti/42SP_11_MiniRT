/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:53:25 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:42:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	gnl_strlen(char *s)
{
	size_t	lenght;

	if (s == NULL)
		return (0);
	lenght = 0;
	while (*s != '\0')
	{
		lenght++;
		s++;
	}
	return (lenght);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*p;
	char	*original_s1;
	size_t	len_string;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	len_string = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len_string);
	if (str == NULL)
		return (NULL);
	p = str;
	original_s1 = s1;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	free(original_s1);
	return (str);
}
