#include "../../include/minirt.h"

static t_bhaskara	solve_bhaskara(t_bhaskara bhask)
{
	bhask.delta = bhask.b * bhask.b - 4 * bhask.a * bhask.c;
	if (bhask.delta > 0)
	{
		bhask.status = TWO_REAL_ROOTS;
		bhask.root1 = (-bhask.b - sqrt(bhask.delta) / (2 * bhask.a));
		bhask.root2 = (-bhask.b + sqrt(bhask.delta) / (2 * bhask.a));
	}
	else if (bhask.delta == 0)
	{
		bhask.status = ONE_REAL_ROOTS;
		bhask.root1 = bhask.root2 = - bhask.b / (2 * bhask.a);
	}
	else
		bhask.status = NO_REAL_ROOTS;
	return (bhask);
}

bool	hit_sphere(const t_sphere *sphere, const t_ray *ray, double *closest_t)
{
	t_vec3	sphere_to_ray;
	t_bhaskara bhask;
	t_bhaskara result;

	sphere_to_ray = subtract_coords(ray->origin, sphere->position);
	bhask.a = dot_product(ray->direction, ray->direction);
	bhask.b = 2.0 * dot_product(sphere_to_ray, ray->direction);
	bhask.c = dot_product(sphere_to_ray, sphere_to_ray) - sphere->diameter * sphere->diameter / 4.0;
	
	result = solve_bhaskara(bhask);
	if (result.status == NO_REAL_ROOTS)
		return (false);
	if (result.root1 > EPSILON && result.root1 < INFINITY)
		*closest_t = result.root1;
	else if (result.root2 > EPSILON && result.root2 < INFINITY)
		*closest_t = result.root2;
	else
		return (false);
	return (true);
}

