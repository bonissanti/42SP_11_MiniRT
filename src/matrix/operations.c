/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:22 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/19 16:09:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
/**
 *
 * Function: matrix_multiply
 * --------------------
 * The multiplication of two matrices are defined by the linear combination
 * of the first lines of matrix 'a' with the columns from matrix 'b'. For
 * each element in the result matrix, the value is calculated as the sum
 * of the products of the corresponding elements in the row of 'a' and the
 * column of 'b'.
 *
 * Iterations:
 * Firsts 2 loops ('y' and 'x'): Index 'y' traverses the rows, index 'x'
 * traverses the columns.
 * Third loop ('i'): This loop performs the sum of products of the elements
 * in the row 'y' on matrix 'a' with the elements in column 'x' on matrix 'b'.
 * The result is multiplied and the sum is storage at result.matrix[y][x].
 *
 * @param str: The input string to be tokenized.
 * @param delim: The delimiter string used to separate the tokens.
 * 
 * @return: A pointer to the next token found in the string, or NULL if no more.
 */

t_matrix	matrix_multiply(const t_matrix *a, const t_matrix *b)
{
	int			y;
	int			x;
	int			i;
	t_matrix	result;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			i = -1;
			result.matrix[y][x] = 0;
			while (++i < 4)
				result.matrix[y][x] += a->matrix[y][i] * b->matrix[i][x];
		}
	}
	return (result);
}

t_matrix	matrix_translate(double	tx, double ty, double tz)
{
	t_matrix	result;

	matrix_identity(&result);
	result.matrix[0][3] = tx;
	result.matrix[1][3] = ty;
	result.matrix[2][3] = tz;
	return (result);
}

t_coords	matrix_multiply_point(const t_matrix *m, const t_coords *point)
{
	t_coords	result;

	result.x = m->matrix[0][0] * point->x + m->matrix[0][1] * point->y + m->matrix[0][2] * point->z + m->matrix[0][3];
	result.y = m->matrix[1][0] * point->x + m->matrix[1][1] * point->y + m->matrix[1][2] * point->z + m->matrix[1][3];
	result.z = m->matrix[2][0] * point->x + m->matrix[2][1] * point->y + m->matrix[2][2] * point->z + m->matrix[2][3];
	return (result);
}

double	det2x2(double a, double b, double c, double d)
{
	return (a * d - b * c);
}

double	det3x3(double m[3][3])
{
	return (m[0][0] * det2x2(m[1][1], m[1][2], m[2][1], m[2][2]) - 
			m[0][1] * det2x2(m[1][0], m[1][2], m[2][0], m[2][2]) +
			m[0][2] * det2x2(m[1][0], m[1][1], m[2][0], m[2][1]));
}
