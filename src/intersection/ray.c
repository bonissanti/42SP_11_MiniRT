/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:14:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/15 11:16:33 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_ray	ray_transform(t_ray ray, t_matrix matrix)
{
	t_ray	transformed_ray;

	transformed_ray.origin = matrix_multiply_coords(matrix, ray.origin);
	transformed_ray.direction = matrix_multiply_vector(matrix, &ray.direction);
	return (transformed_ray);
}

t_coords	ray_position(t_ray ray, double distance)
{
	t_coords	position;

	position.x = ray.origin.x + distance * ray.direction.x;
	position.y = ray.origin.y + distance * ray.direction.y;
	position.z = ray.origin.z + distance * ray.direction.z;
	return (position);
}

