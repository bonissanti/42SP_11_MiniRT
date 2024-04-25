/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:00:08 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/23 15:07:02 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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
