/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:58:07 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/20 18:35:07 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_bhaskara	solve_bhaskara(t_bhaskara bhask)
{
	bhask.delta = bhask.b * bhask.b - 4 * bhask.a * bhask.c;
	if (bhask.delta > 0)
	{
		bhask.status = TWO_REAL_ROOTS;
		bhask.root1 = (-bhask.b - sqrt(bhask.delta)) / (2 * bhask.a);
		bhask.root2 = (-bhask.b + sqrt(bhask.delta)) / (2 * bhask.a);
	}
	else if (bhask.delta == 0)
	{
		bhask.status = ONE_REAL_ROOTS;
		bhask.root1 = bhask.root2 = -bhask.b / (2 * bhask.a);
	}
	else
		bhask.status = NO_REAL_ROOTS;
	return (bhask);
}

bool	hit_sphere(const t_sphere *sphere, t_ray ray, double *t)
{
	t_vec3	sphere_to_ray;
	t_bhaskara bhask;
	t_bhaskara result;

	init_bhask(&bhask, &result);
	sphere_to_ray = subtract_coords(ray.origin, sphere->position);
	bhask.a = dot_product(ray.direction, ray.direction);
	bhask.b = 2.0 * dot_product(sphere_to_ray, ray.direction);
	bhask.c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	bhask.delta = bhask.b * bhask.b - 4 * bhask.a * bhask.c;
	if (bhask.delta < 0)
		return (false);
	t[0] = (-bhask.b - sqrt(bhask.delta)) / (2 * bhask.a);
	t[1] = (-bhask.b + sqrt(bhask.delta)) / (2 * bhask.a);
	return (true);
}

// bool	hit_sphere(const t_sphere *sphere, t_ray ray, t_inter *xs)
// {
// 	t_vec3	sphere_to_ray;
// 	t_bhaskara bhask;
// 	t_bhaskara result;
//
// 	init_bhask(&bhask, &result);
// 	sphere_to_ray = subtract_coords(ray.origin, sphere->position);
// 	bhask.a = dot_product(ray.direction, ray.direction);
// 	bhask.b = 2.0 * dot_product(sphere_to_ray, ray.direction);
// 	bhask.c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
//
// 	result = solve_bhaskara(bhask);
// 	if (result.status == NO_REAL_ROOTS)
// 		return (false);
// 	if (result.root1 > EPSILON && result.root1 < INFINITY)
// 		xs->t[0] = result.root1;
// 	else if (result.root2 > EPSILON && result.root2 < INFINITY && result.root1 < result.root2)
// 		xs->t[1] = result.root2;
// 	else
// 		return (false);
// 	return (true);
// }

bool	hit_cylinder(const t_cylinder *cyl, t_ray ray, double t[2])
{
	t_bhaskara	bhask;
	t_bhaskara	result;
	bool		found_intersection;

	init_bhask(&bhask, &result);
	bhask.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	if (check_equal_doubles(bhask.a, 0))
		return (false);
	bhask.b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z
		* ray.direction.z;
	bhask.c = (ray.origin.x * ray.origin.x) + (ray.origin.z * ray.origin.z) - 1;
	result = solve_bhaskara(bhask);
	if (result.status == NO_REAL_ROOTS)
		return (false);
	found_intersection = false;
	if (result.root1 > 0)
	{
		t[0] = t[1] = result.root1;
		found_intersection = true;
	}
	if (result.root2 > 0)
	{
		if (!found_intersection || result.root2 < t[0])
		{
			t[1] = t[0];
			t[0] = result.root2;
		}
		else
			t[1] = result.root2;
		found_intersection = true;
	}
	if (found_intersection)
	{
		double intersection_y = (ray.origin.y - (cyl->height / 2)) + t[0] * ray.direction.y;
		if (intersection_y < cyl->min || intersection_y > cyl->max)
			t[0] = INFINITY;
		intersection_y = (ray.origin.y  - (cyl->height / 2)) + t[1] * ray.direction.y;
		if (intersection_y < cyl->min || intersection_y > cyl->max)
			t[1] = INFINITY;
	}
	return (found_intersection);
}

bool	hit_plane(t_ray ray, double t[2])
{
	if (fabs(ray.direction.y) < EPSILON)
		return (false);
	else
		t[0] = -ray.origin.y / ray.direction.y;
	return (true);
}
