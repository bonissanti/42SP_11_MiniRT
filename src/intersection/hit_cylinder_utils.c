/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:49:24 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:59:54 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static bool	check_cap(t_ray ray, double t, double radius)
{
	double	x;
	double	z;

	(void)radius;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return (x * x + z * z <= 1);
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

bool	set_t(t_bhaskara result, double t[2])
{
	bool	found_intersection;

	found_intersection = false;
	if (result.root1 > 0)
	{
		t[0] = result.root1;
		t[1] = t[0];
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
	return (found_intersection);
}

t_bhaskara	cylinder_bhask(const t_ray ray)
{
	t_bhaskara	bhask;

	bhask.a = (ray.direction.x * ray.direction.x) + (ray.direction.z
			* ray.direction.z);
	bhask.b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z
		* ray.direction.z;
	bhask.c = (ray.origin.x * ray.origin.x) + (ray.origin.z * ray.origin.z) - 1;
	return (bhask);
}
