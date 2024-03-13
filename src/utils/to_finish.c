/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:18 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:35:19 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void    free_array(char **array)
{
    char **ptr;

    ptr = array;
    while (*ptr)
    {
        free(*ptr);
        ptr++;
    }
    free(array);
}

int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (ERROR);
}
