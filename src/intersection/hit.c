/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:58:07 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 13:00:43 by brunrodr         ###   ########.fr       */
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
	bool		found_intersection;
	double		intersection_y;

	init_bhask(&bhask, &result);
	bhask = cylinder_bhask(ray);
	if (check_equal_doubles(bhask.a, 0))
		return (intersect_caps(cyl, ray, t));
	result = solve_bhaskara(bhask);
	if (result.status == NO_REAL_ROOTS)
		return (false);
	found_intersection = set_t(result, t);
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
