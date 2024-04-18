/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:58:07 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 13:14:51 by brunrodr         ###   ########.fr       */
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

bool	hit_cylinder(const t_cylinder *cyl, t_ray ray, double t[2])
{
	t_bhaskara	bhask;
	t_bhaskara	result;
	double		y1;
	double		y2;
	bool		within_limits_t1;
	bool		within_limits_t2;
	bool		found_intersection;

	init_bhask(&bhask, &result);
	bhask.a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	if (check_equal_doubles(bhask.a, 0))
		return (false);
	bhask.b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z
			* ray.direction.z);
	bhask.c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
	result = solve_bhaskara(bhask);
	if (result.status == NO_REAL_ROOTS)
		return (false);
	// verifica os limites de altura ṕara as duas raizes
	y1 = ray.origin.y + bhask.root1 * ray.direction.y;
	y2 = ray.origin.y + bhask.root2 * ray.direction.y;
	within_limits_t1 = y1 >= cyl->min && y1 <= cyl->max;
	within_limits_t2 = y2 >= cyl->min && y2 <= cyl->max;
	// define as interseções
	found_intersection = false;
	if (result.status == TWO_REAL_ROOTS || result.status == ONE_REAL_ROOTS)
	{
		if (result.root1 > 0 && within_limits_t1)
		{
			t[0] = t[1] = result.root1;
			found_intersection = true;
		}
		if (result.root2 > 0 && within_limits_t2)
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
