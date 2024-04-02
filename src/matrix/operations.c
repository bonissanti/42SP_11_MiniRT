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

t_matrix	matrix_multiply(t_matrix *a, t_matrix *b)
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
// # ifndef TEST
// 	printf("a\n");
// 	print_matrix(*a);
// 	printf("b\n");
// 	print_matrix(*b);
// 	printf("result\n");
// 	print_matrix(result);
// 	printf("\n");
// # endif
	return (result);
}

t_matrix	scaling_matrix(double sx, double sy, double sz)
{
	t_matrix	scaling;

	matrix_identity(&scaling);
	scaling.matrix[0][0] = sx;
	scaling.matrix[1][1] = sy;
	scaling.matrix[2][2] = sz;
	return (scaling);	
}

t_matrix	translation_matrix(double	tx, double ty, double tz)
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

t_matrix	rotation_matrix_x(double angle)
{
	t_matrix	rotation;
	double		rad;

	matrix_identity(&rotation);
	rad = angle * M_PI / 180.0;

	rotation.matrix[1][1] = cos(rad);
	rotation.matrix[1][2] = -sin(rad);
	rotation.matrix[2][1] = sin(rad);
	rotation.matrix[2][2] = cos(rad);
	return (rotation);
}

t_matrix	rotation_matrix_y(double angle)
{
	t_matrix	rotation;
	double		rad;

	matrix_identity(&rotation);
	rad = angle * M_PI / 180.0;

	rotation.matrix[0][0] = cos(rad);
	rotation.matrix[0][2] = sin(rad);
	rotation.matrix[2][0] = -sin(rad);
	rotation.matrix[2][2] = cos(rad);
	return (rotation);
}

t_matrix rotation_matrix_z(double angle)
{
	t_matrix	rotation;
	double		rad;

	matrix_identity(&rotation);
	rad = angle * M_PI / 180.0;

	rotation.matrix[0][0] = cos(rad);
	rotation.matrix[0][1] = -sin(rad);
	rotation.matrix[1][0] = sin(rad);
	rotation.matrix[1][1] = cos(rad);
	return (rotation);
}

t_quatern	create_rotation_quatern(t_vec3 orientation, double radians)
{
	t_quatern	quat;
	// orientation = normalize_vector(orientation);
	double	half_angle = -M_PI / 4.0;
	
	(void)orientation;
	(void)radians;
	quat.w = cos(half_angle);
	quat.x = sin(half_angle);
	quat.y = 0.0;
	quat.z = 0.0;
	return (quat);
}

t_matrix	quatern_to_matrix(t_vec3 orientation, double radians)
{
	t_matrix	rotation;
	t_quatern	quat;

	quat = create_rotation_quatern(orientation, radians);
	double xx = quat.x * quat.x;
	double yy = quat.y * quat.y;
	double zz = quat.z * quat.z;
	double xy = quat.x * quat.y;
	double xz = quat.x * quat.z;
	double yz = quat.y * quat.z;
	double wx = quat.w * quat.x;
	double wy = quat.w * quat.y;
	double wz = quat.w * quat.z;

	rotation.matrix[0][0] = 1.0 - 2.0 * (yy + zz);
	rotation.matrix[0][1] = 2.0 * (xy - wz);
	rotation.matrix[0][2] = 2.0 * (xz + wy);
	rotation.matrix[0][3] = 0.0;

	rotation.matrix[1][0] = 2.0 * (xy + wz);
	rotation.matrix[1][1] = 1.0 - 2.0 * (xx + zz);
	rotation.matrix[1][2] = 2.0 * (yz - wx);
	rotation.matrix[1][3] = 0.0;

	rotation.matrix[2][0] = 2.0 * (xz - wy);
	rotation.matrix[2][1] = 2.0 * (yz + wx);
	rotation.matrix[2][2] = 1.0 - 2.0 * (xx + yy);
	rotation.matrix[2][3] = 0.0;

	rotation.matrix[3][0] = 0.0;
	rotation.matrix[3][1] = 0.0;
	rotation.matrix[3][2] = 0.0;
	rotation.matrix[3][3] = 1.0;
	return (rotation);
}

//BUG: Essa versão de baixo não funciona com orientação 0,0,1. Na fórmula de Euler
// isso seria o Roll. Tem que testar pra ver como ele aparece
// t_matrix	get_rotation_matrix(t_matrix original)
// {
// 	t_matrix	rotation;
// 	double		w = original.matrix[0][0]
// 	double		x = original.matrix
// 	double		scale_factor = 2.0/ (ma)
//
//
// }

//WARNING: As duas funções abaixo não estão sendo usadas no momento
// double	det2x2(double a, double b, double c, double d)
// {
// 	return (a * d - b * c);
// }
//
// double	det3x3(double m[3][3])
// {
// 	return (m[0][0] * det2x2(m[1][1], m[1][2], m[2][1], m[2][2]) - 
// 			m[0][1] * det2x2(m[1][0], m[1][2], m[2][0], m[2][2]) +
// 			m[0][2] * det2x2(m[1][0], m[1][1], m[2][0], m[2][1]));
// }
