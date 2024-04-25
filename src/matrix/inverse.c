/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:03:11 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:05:59 by brunrodr         ###   ########.fr       */
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

double	determinant(t_matrix *original)
{
	int		j;
	double	det;
	double	cofactor;

	if (original->rows == 1)
		return (original->matrix[0][0]);
	j = -1;
	det = 0;
	while (++j < original->rows)
	{
		cofactor = calculate_cofactor(original, 0, j);
		det += original->matrix[0][j] * cofactor;
	}
	return (det);
}

void	invert_matrix(t_matrix *original, t_matrix *inverted)
{
	int			i;
	int			j;
	double		det;
	t_matrix	cofactor;
	t_matrix	transposed;

	det = determinant(original);
	if (det == 0)
		return ;
	cofactor = cofactor_matrix(original);
	transposed = transpose_matrix(&cofactor);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			inverted->matrix[i][j] = transposed.matrix[i][j] / det;
	}
}
