/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:30:05 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:42:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_comps	prepare_comps(t_inter inter, t_ray ray)
{
	t_comps	computations;

	computations.t = inter.t;
	computations.point = get_intersection_point(ray, inter.t);
	computations.eyev = multiply_vector(ray.direction, -1);
	computations.normalv = get_normal(inter.object, computations.point);
	computations.normalv = is_inside(computations.eyev, computations.normalv);
	computations.over_point = add_coords(computations.point,
			multiply_vector(computations.normalv, EPSILON));
	computations.reflectv = reflect_vector(ray.direction, computations.normalv);
	computations.object = inter.object;
	return (computations);
}
