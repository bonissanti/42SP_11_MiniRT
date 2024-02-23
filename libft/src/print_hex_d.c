/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:18:53 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:46:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	putnbr_hex(unsigned int arg, int base, int uppercase)
{
	int	length;

	length = 0;
	if (arg >= (unsigned int)base)
		length += putnbr_hex((arg / base), base, uppercase);
	if (arg % base < 10)
		ft_putchar(arg % base + '0');
	else
	{
		if (uppercase)
			ft_putchar(arg % base + 'A' - 10);
		else
			ft_putchar(arg % base + 'a' - 10);
	}
	length++;
	return (length);
}

int	print_hex_d(unsigned int arg, int uppercase, t_flags flags)
{
	int	length;

	length = 0;
	if (arg == 0)
		return (write(1, "0", 1));
	if (flags.hashtag == 1)
	{
		if (uppercase == 1)
			length += write(1, "0X", 2);
		else
			length += write(1, "0x", 2);
	}
	length += putnbr_hex(arg, 16, uppercase);
	return (length);
}
