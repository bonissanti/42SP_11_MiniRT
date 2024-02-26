/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:25:46 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	absolute_value;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		absolute_value = n * -1;
	}
	else
		absolute_value = n;
	if (absolute_value >= 10)
		ft_putnbr_fd((absolute_value / 10), fd);
	ft_putchar_fd((absolute_value % 10) + '0', fd);
}
