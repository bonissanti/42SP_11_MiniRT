/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:45:16 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	numlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	reverse_string(char *str)
{
	char	*start;
	char	*end;
	char	temp;

	start = str;
	end = str + ft_strlen(str) - 1;
	if (*str == '-')
	{
		start++;
	}
	while (start < end)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

char	*allocate_string(long int n1, int len)
{
	char	*str;

	if (n1 == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	char		*p;
	int			len;
	long int	n1;

	n1 = n;
	len = numlen(n1);
	str = allocate_string(n1, len);
	p = str;
	if (!str)
		return (NULL);
	if (n1 < 0)
	{
		*p++ = '-';
		n1 = n1 * -1;
	}
	while (n1 > 0)
	{
		*p++ = (n1 % 10) + '0';
		n1 = n1 / 10;
		*p = '\0';
	}
	reverse_string(str);
	return (str);
}
