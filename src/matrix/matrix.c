/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:17 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 11:59:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	matrix_identity(t_matrix *mat)
{
	int	y;
	int	x;

	y = -1;
	mat->rows = 4;
	mat->cols = 4;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (y == x)
				mat->matrix[y][x] = 1.0;
			else
				mat->matrix[y][x] = 0.0;
		}
	}
}
