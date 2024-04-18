/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:42 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 11:58:44 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_matrix	transpose_matrix(t_matrix *original)
{
	int			i;
	int			j;
	t_matrix	transposed;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			transposed.matrix[i][j] = original->matrix[j][i];
	}
	return (transposed);
}

void	create_submatrix(t_matrix *original, t_matrix *submatrix, int row_ign,
	int col_ign)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = -1;
	k = 0;
	while (++i < original->rows)
	{
		j = -1;
		l = 0;
		if (i == row_ign)
			continue ;
		while (++j < original->cols)
		{
			if (j == col_ign)
				continue ;
			submatrix->matrix[k][l++] = original->matrix[i][j];
		}
		k++;
	}
}
