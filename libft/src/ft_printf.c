/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:30:09 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:46:10 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	convert_specifiers(const char *format, va_list args, int index)
{
	int		upper;
	t_flags	flags;

	flags = (t_flags){0, 0, 0};
	index = 0;
	if (*format++ == '%')
	{
		active_flags(&format, &flags);
		upper = check_uppercase(*format);
		if (*format == 'c')
			index += print_char(va_arg(args, int));
		else if (*format == 's')
			index += print_string(va_arg(args, char *));
		else if (*format == 'p')
			index += print_pointer(va_arg(args, unsigned long int), 16);
		else if (*format == 'u')
			index += print_unsign_int(va_arg(args, unsigned int));
		else if (*format == 'd' || *format == 'i')
			index += print_int(va_arg(args, int), flags);
		else if (*format == 'x' || *format == 'X')
			index += print_hex_d(va_arg(args, unsigned long int), upper, flags);
		else if (*format == '%')
			index += print_percent();
	}
	return (index);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		index;
	int		specifier_length;

	index = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			specifier_length = get_specifier_length(str);
			index += convert_specifiers(str, args, index);
			str += specifier_length;
		}
		else
		{
			index += write(1, str, 1);
			str++;
		}
	}
	va_end(args);
	return (index);
}
