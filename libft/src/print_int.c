/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:17:28 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:46:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	putnbr_int(int arg, int base)
{
	int				length;
	unsigned int	absolute_arg;

	length = 0;
	if (arg < 0)
	{
		length += write(1, "-", 1);
		absolute_arg = (unsigned int)(arg * -1);
	}
	else
		absolute_arg = (unsigned int)arg;
	if (absolute_arg >= (unsigned int)base)
		length += putnbr_int((absolute_arg / base), base);
	ft_putchar(absolute_arg % base + '0');
	length++;
	return (length);
}

int	print_int(int arg, t_flags flags)
{
	int	length;

	length = 0;
	if (flags.plus == 1 && arg >= 0)
		length += write(1, "+", 1);
	else if (flags.space == 1 && arg >= 0)
		length += write(1, " ", 1);
	length += putnbr_int(arg, 10);
	return (length);
}
