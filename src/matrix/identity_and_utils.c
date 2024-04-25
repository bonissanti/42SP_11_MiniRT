/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_and_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:17 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:06:21 by brunrodr         ###   ########.fr       */
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

double	calculate_minor(t_matrix *original, int row_ign, int col_ign)
{
	t_matrix	submatrix;
	double		minor;

	submatrix.rows = original->rows - 1;
	submatrix.cols = original->cols - 1;
	create_submatrix(original, &submatrix, row_ign, col_ign);
	minor = determinant(&submatrix);
	return (minor);
}

double	calculate_cofactor(t_matrix *original, int i, int j)
{
	double	minor;

	minor = calculate_minor(original, i, j);
	if ((i + j) % 2 == 0)
		return (minor);
	else
		return ((-1) * minor);
}

t_matrix	cofactor_matrix(t_matrix *original)
{
	int			i;
	int			j;
	t_matrix	cofactor;

	i = -1;
	while (++i < original->rows)
	{
		j = -1;
		while (++j < original->cols)
			cofactor.matrix[i][j] = calculate_cofactor(original, i, j);
	}
	return (cofactor);
}
