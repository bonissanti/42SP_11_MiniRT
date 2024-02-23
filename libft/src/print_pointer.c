/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:26:32 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:46:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	putnbr_ptr(unsigned long int arg, int base)
{
	int	length;

	length = 0;
	if (arg >= (unsigned long int)base)
		length += putnbr_ptr((arg / base), base);
	if (arg % base < 10)
		ft_putchar(arg % base + '0');
	else
		ft_putchar(arg % base + 'a' - 10);
	length++;
	return (length);
}

int	print_pointer(unsigned long int arg, int base)
{
	int	length;

	length = 0;
	if (!arg)
	{
		length += write(1, "(nil)", 5);
		return (length);
	}
	length += write(1, "0x", 2);
	length += putnbr_ptr(arg, base);
	return (length);
}
