/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:58:07 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/23 15:20:57 by brunrodr         ###   ########.fr       */
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
		bhask.root1 = -bhask.b / (2 * bhask.a);
		bhask.root2 = bhask.root1;
	}
	else
		bhask.status = NO_REAL_ROOTS;
	return (bhask);
}

bool	hit_sphere(const t_sphere *sphere, t_ray ray, double *t)
{
	t_vec3		sphere_to_ray;
	t_bhaskara	bhask;
	t_bhaskara	result;

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

bool	check_cap(t_ray ray, double t, double radius)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return (x * x + z * z <= radius * radius);
}

bool	intersect_caps(const t_cylinder *cyl, t_ray ray, double t[2])
{
	double	t_cap;
	bool	found_intersection;

	found_intersection = false;
	t_cap = (cyl->min - (ray.origin.y)) / ray.direction.y;
	if (check_cap(ray, t_cap, cyl->diameter * 2))
	{
		if (t_cap > EPSILON && t_cap < t[0])
		{
			t[0] = t_cap;
			found_intersection = true;
		}
	}
	t_cap = (cyl->max - (ray.origin.y)) / ray.direction.y;
	if (check_cap(ray, t_cap, cyl->diameter * 2))
	{
		if (t_cap > EPSILON && t_cap < t[1])
		{
			t[1] = t_cap;
			found_intersection = true;
		}
	}
	return (found_intersection);
}

bool	hit_cylinder(const t_cylinder *cyl, t_ray ray, double t[2])
{
	t_bhaskara	bhask;
	t_bhaskara	result;
	bool		found_intersection;
	double		intersection_y;

	init_bhask(&bhask, &result);
	bhask.a = (ray.direction.x * ray.direction.x) + (ray.direction.z
			* ray.direction.z);
	if (check_equal_doubles(bhask.a, 0))
		return (intersect_caps(cyl, ray, t));
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
		intersection_y = (ray.origin.y) + t[0] * ray.direction.y;
		if (intersection_y < cyl->min || intersection_y > cyl->max)
			t[0] = INFINITY;
		intersection_y = (ray.origin.y) + t[1] * ray.direction.y;
		if (intersection_y < cyl->min || intersection_y > cyl->max)
			t[1] = INFINITY;
	}
	intersect_caps(cyl, ray, t);
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
