/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots_and_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:16:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:36:13 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool	check_equal_doubles(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}

t_vec3	cross_vector(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	matrix_multiply_vector(const t_matrix m, const t_vec3 *point)
{
	t_vec3	result;

	result.x = m.matrix[0][0] * point->x + m.matrix[0][1] * point->y
		+ m.matrix[0][2] * point->z;
	result.y = m.matrix[1][0] * point->x + m.matrix[1][1] * point->y
		+ m.matrix[1][2] * point->z;
	result.z = m.matrix[2][0] * point->x + m.matrix[2][1] * point->y
		+ m.matrix[2][2] * point->z;
	return (result);
}

t_vec3	is_inside(t_vec3 eyev, t_vec3 normal)
{
	if (dot_product(eyev, normal) < 0)
		return (multiply_vector(normal, -1));
	return (normal);
}
