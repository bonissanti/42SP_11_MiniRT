/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:15:27 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t num_elem, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = num_elem * size;
	if (num_elem == 0 || size == 0)
	{
		return (malloc(0));
	}
	else if (total_size / num_elem != size)
		return (NULL);
	ptr = malloc(sizeof(char) * (num_elem * size));
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, num_elem * size);
	return (ptr);
}
