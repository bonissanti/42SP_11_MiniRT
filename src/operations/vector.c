/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:35:24 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	set_vector(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	normalize_vector(t_vec3 value)
{
	double	magnitude;
	t_vec3	normalized;

	ft_memset(&normalized, 0, sizeof(t_vec3));
	magnitude = sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
	if (magnitude != 0)
	{
		normalized.x = value.x / magnitude;
		normalized.y = value.y / magnitude;
		normalized.z = value.z / magnitude;
	}
	return (normalized);
}

t_vec3	subtract_vector(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

double	vector_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

bool	compare_vectors(t_vec3 result, t_vec3 expected)
{
	if (check_equal_doubles(result.x, expected.x)
		&& check_equal_doubles(result.y, expected.y)
		&& check_equal_doubles(result.z, expected.z))
		return (true);
	return (false);
}
