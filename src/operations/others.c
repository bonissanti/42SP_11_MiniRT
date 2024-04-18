/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:24:09 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 12:27:08 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool	check_equal_doubles(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}

bool	compare_vectors(t_vec3 result, t_vec3 expected)
{
	if (check_equal_doubles(result.x, expected.x)
		&& check_equal_doubles(result.y, expected.y)
		&& check_equal_doubles(result.z, expected.z))
		return (true);
	return (false);
}

double	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
