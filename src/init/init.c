/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:33 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 11:42:05 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_structs(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
}

void	init_bhask(t_bhaskara *bhask, t_bhaskara *result)
{
	ft_memset(bhask, 0, sizeof(t_bhaskara));
	ft_memset(result, 0, sizeof(t_bhaskara));
}
