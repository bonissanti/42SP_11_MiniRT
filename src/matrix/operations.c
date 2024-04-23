/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:22 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/23 15:22:40 by renato           ###   ########.fr       */
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

	matrix_identity(&result);
	y = -1;
	matrix_identity(&result);
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

t_coords	matrix_multiply_coords(t_matrix original, const t_coords coords)
{
	t_matrix	coord_mat;
	t_matrix	result_mat;
	t_coords	result;

	matrix_identity(&coord_mat);
	coord_mat.matrix[0][0] = coords.x;
	coord_mat.matrix[1][0] = coords.y;
	coord_mat.matrix[2][0] = coords.z;
	coord_mat.matrix[3][0] = 1.0;

	result_mat = matrix_multiply(&original, &coord_mat);
	result.x = result_mat.matrix[0][0];
	result.y = result_mat.matrix[1][0];
	result.z = result_mat.matrix[2][0];
	return (result);
}

t_matrix	simple_rotation_x(double angle)
{
	t_matrix	rotation;

	matrix_identity(&rotation);
	rotation.matrix[1][1] = cos(angle);
	rotation.matrix[1][2] = -sin(angle);
	rotation.matrix[2][1] = sin(angle);
	rotation.matrix[2][2] = cos(angle);
	return (rotation);
}

t_matrix	simple_rotation_y(double angle)
{
	t_matrix	rotation;

	matrix_identity(&rotation);
	rotation.matrix[0][0] = cos(angle);
	rotation.matrix[0][2] = sin(angle);
	rotation.matrix[2][0] = -sin(angle);
	rotation.matrix[2][2] = cos(angle);
	return (rotation);
}

t_matrix simple_rotation_z(double angle)
{
	t_matrix	rotation;

	matrix_identity(&rotation);
	rotation.matrix[0][0] = cos(angle);
	rotation.matrix[0][1] = -sin(angle);
	rotation.matrix[1][0] = sin(angle);
	rotation.matrix[1][1] = cos(angle);
	return (rotation);
}

t_matrix	arbitrary_rotation_xy(double x_angle, double y_angle)
{
	t_matrix	result;
	t_matrix	rotation_x;
	t_matrix	rotation_y;

	rotation_x = simple_rotation_x(x_angle);
	rotation_y = simple_rotation_y(y_angle);
	result = matrix_multiply(&rotation_x, &rotation_y);
	return (result);
}

t_matrix	arbitrary_rotation_zx(double z_angle, double x_angle)
{
	t_matrix	result;
	t_matrix	rotation_z;
	t_matrix	rotation_x;

	rotation_z = simple_rotation_z(z_angle);
	rotation_x = simple_rotation_x(x_angle);
	result = matrix_multiply(&rotation_z, &rotation_x);
	return (result);
}

/**
 * Function: verify_orientation
 * --------------------
 * This funtion verify the orientation of a vector 3D and returns a rotation matrix.
 * If orientation corresponds to a mainly axis (or opposites), this function will return
 * a simple rotation in this specific axis. 
 * 
 * @param str: The input string to be searched.
 * @param set: The set of characters to be used for comparison, 
 * depending on the mode.
 * @param mode: Determines the function mode; 0 for strspn mode, 1 for 
 * strcspn mode.
 *
 * @return: The length of the initial segment of 'str' based on the selected 
 * mode.
 */

t_matrix	verify_orientation(t_vec3 orientation)
{
	t_matrix	rotation;

	matrix_identity(&rotation);
	if (compare_vectors(orientation, set_vector(0, 1, 0)))
		return (rotation);
	else if (compare_vectors(orientation, set_vector(0, -1, 0)))
		return (simple_rotation_x(M_PI)); // 180 
	else if (compare_vectors(orientation, set_vector(1, 0, 0)))
		return (simple_rotation_z(-M_PI / 2)); // 90
	else if (compare_vectors(orientation, set_vector(-1, 0, 0)))
		return (simple_rotation_z(M_PI / 2));
	else if (compare_vectors(orientation, set_vector(0, 0, 1)))
		return (simple_rotation_x(M_PI / 2));
	else if (compare_vectors(orientation, set_vector(0, 0, -1)))
		return (simple_rotation_x(-M_PI / 2));
	if (check_equal_doubles(orientation.y, 0))
		return (arbitrary_rotation_xy(M_PI / 2, atan2(orientation.x, orientation.z)));
	else
	 	return (arbitrary_rotation_zx(atan2(orientation.z, orientation.y), atan2(-orientation.x, orientation.y)));
}
