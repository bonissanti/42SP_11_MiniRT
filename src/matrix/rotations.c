/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:57:51 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 11:59:31 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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

t_matrix	simple_rotation_z(double angle)
{
	t_matrix	rotation;

	matrix_identity(&rotation);
	rotation.matrix[0][0] = cos(angle);
	rotation.matrix[0][1] = -sin(angle);
	rotation.matrix[1][0] = sin(angle);
	rotation.matrix[1][1] = cos(angle);
	return (rotation);
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

t_matrix	arbitrary_rotation_xy(double x_angle, double y_angle)
{
	t_matrix	result;
	t_matrix	rotation_x;
	t_matrix	rotation_y;

	rotation_x = simple_rotation_x(x_angle);
	rotation_y = simple_rotation_y(y_angle);
	result = matrix_multiply(&rotation_y, &rotation_x);
	return (result);
}

t_matrix	arbitrary_rotation_zx(double z_angle, double x_angle)
{
	t_matrix	result;
	t_matrix	rotation_z;
	t_matrix	rotation_x;

	rotation_z = simple_rotation_z(z_angle);
	rotation_x = simple_rotation_x(x_angle);
	result = matrix_multiply(&rotation_x, &rotation_z);
	return (result);
}
