/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:03:36 by renato            #+#    #+#             */
/*   Updated: 2024/04/23 23:47:15 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	reflect_vector(t_vec3 in, t_vec3 normal)
{
	return (subtract_vector(in, multiply_vector(normal,
				2 * dot_product(in, normal))));
}

void	intersect_object(t_ray ray, t_object *obj, double *t,
	t_object *origin_obj)
{
	t[0] = -1.0;
	t[1] = -1.0;
	
	if (obj == origin_obj)
		return ;
	if (obj->type == SPHERE)
		hit_sphere((t_sphere *)obj->object, ray_transform(ray,
				get_geo(obj).sphere->inversed_t), t);
	else if (obj->type == PLANE)
		hit_plane(ray_transform(ray,
				get_geo(obj).plane->inversed_t), t);
	else if (obj->type == CYLINDER)
		hit_cylinder((t_cylinder *)obj->object, ray_transform(ray,
				get_geo(obj).cylinder->inversed_t), t);
}

bool is_in_shadow(t_comps *closest, t_light light, t_object *objects)
{
	t_object	*obj;
	t_ray		shadow_ray;
	double		light_distance;
	double		t[2];

	shadow_ray.origin = closest->over_point;
	shadow_ray.direction = normalize_vector(subtract_tuple(light.position,
				shadow_ray.origin));
	light_distance = vector_length(subtract_tuple(light.position,
				shadow_ray.origin));
	obj = objects;
	while (obj != NULL)
	{
		intersect_object(shadow_ray, obj, t, closest->object);
		if ((t[0] > EPSILON && t[0] < light_distance)
			|| (t[1] > EPSILON && t[1] < light_distance))
			return (true);
		obj = obj->next;
	}
	return (false);
}

t_color	get_diffuse(t_color ambient, t_comps comps, t_data data,
	t_color_data c_data)
{
	t_color		diffuse;
	t_color		specular;
	t_vec3		reflect;
	double		reflect_dot_eye;
	double		factor;

	diffuse = multiply_color(c_data.color, DIFFUSE * c_data.light_dot_normal);
	reflect = reflect_vector(multiply_vector(c_data.light, -1), comps.normalv);
	reflect_dot_eye = dot_product(reflect, comps.eyev);
	if (reflect_dot_eye < 0)
		return (add_colors(ambient, diffuse));
	else
	{
		factor = pow(reflect_dot_eye, SHININESS);
		specular = multiply_color((t_color){data.light.brightness,
				data.light.brightness, data.light.brightness, 1},
				SPECULAR * factor);
		return (add_colors(add_colors(ambient, diffuse), specular));
	}
}

t_color	get_color(t_data *data, t_comps *closest)
{
	t_color		color;
	t_color		ambient;
	t_vec3		light;
	double		light_dot_normal;

	if (closest->object->type == SPHERE)
		color = set_color(get_geo(closest->object).sphere->color);
	else if (closest->object->type == PLANE)
		color = set_color(get_geo(closest->object).plane->color);
	else
		color = set_color(get_geo(closest->object).cylinder->color);
	color = multiply_color(color, data->light.brightness);
	light = normalize_vector(subtract_coords(data->light.position,
				closest->over_point));
	ambient = multiply_color(set_color(data->amblight.color), data->amblight.ratio);
    ambient = add_colors(ambient, color);
	light_dot_normal = dot_product(light, closest->normalv);
	if (light_dot_normal < 0
		|| is_in_shadow(closest, data->light, data->objects))
		return (set_to_range_color(ambient));
	return (set_to_range_color(get_diffuse(ambient, *closest, *data,
				(t_color_data){color, light, light_dot_normal})));
}
