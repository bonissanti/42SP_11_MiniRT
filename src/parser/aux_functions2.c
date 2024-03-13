/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:53 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:36:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	set_vector_3d(char *vector_line)
{
	char **vector_split;

	vector_split = ft_split(vector_line, ',');
	if (count_token(vector_split, 3, "Incorrect number of vector, e.g[0,0,1]"))
		return (ERROR);
	if (validate_numbers_dot(vector_split) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	if (validate_range_3d(vector_split) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	if (normalize_and_set(vector_split) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	free_array(vector_split);
	return (OK);
}

int validate_range_3d(char **str)
{
	int	i;
	int	range;

	i = -1;
	while (++i < 3)
	{
		range = ft_atod(str[i]);
		if (range < -1.0 || range > 1.0)
			return (print_error("Value out of range, e.g [-1.1,0.0,1.0]"));
	}
	return (OK);
}


int	normalize_and_set(char **vector_str)
{
	double	x;
	double	y;
	double	z;
	double	magnitude;

	x = ft_atod(vector_str[0]);
	y = ft_atod(vector_str[1]);
	z = ft_atod(vector_str[2]);
	magnitude = sqrt(x * x + y * y + z * z);

	if (fabs(magnitude) < EPSILON)
		return (print_error("Cannot normalize a zero vector"));
	return (OK);
}
