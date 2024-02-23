/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:08:53 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:46:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putchar(char c)
{
	int len;

	len = 0;
	len += write(1, &c, 1);
	return (len);
}

int	get_specifier_length(const char *format)
{
	int	length;

	length = 1;
	if (*format == '%')
		format++;
	while (*format == '#' || *format == '0' || *format == '-' || *format == '+'
		|| *format == ' ')
	{
		format++;
		length++;
	}
	if (*format == 'c' || *format == 's' || *format == 'p' || *format == 'd'
		|| *format == 'i' || *format == 'u' || *format == 'x' || *format == 'X'
		|| *format == '%')
		length++;
	return (length);
}

void	active_flags(const char **format, t_flags *flags)
{
	char	flag;

	while (**format == '#' || **format == '0' || **format == '-'
		|| **format == '+' || **format == ' ')
	{
		flag = **format;
		if (flag == '#')
			flags->hashtag = 1;
		else if (flag == '+')
			flags->plus = 1;
		else if (flag == ' ')
			flags->space = 1;
		(*format)++;
	}
}

int	check_uppercase(const char format)
{
	if (format == 'X')
		return (1);
	return (0);
}
