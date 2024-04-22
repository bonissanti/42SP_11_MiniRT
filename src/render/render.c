/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/22 18:34:45 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

t_geo_u	get_geo(t_object *object)
{
	t_geo_u	geo;

	if (object->type == SPHERE)
		geo.sphere = (t_sphere *)object->object;
	else if (object->type == PLANE)
		geo.plane = (t_plane *)object->object;
	else if (object->type == CYLINDER)
		geo.cylinder = (t_cylinder *)object->object;
	else
		geo.sphere = NULL;
	return (geo);
}

t_vec3	reflect_vector(t_vec3 in, t_vec3 normal)
{
	return (subtract_vector(in, multiply_vector(normal,
				2 * dot_product(in, normal))));
}

typedef struct s_color_data //MOVE THIS
{
	t_color		color;
	t_vec3		light;
	double		light_dot_normal;
}	t_color_data;

t_vec3	is_inside(t_vec3 eyev, t_vec3 normal)
{

	if (dot_product(eyev, normal) >= 0)
		return (normal);
	normal = multiply_vector(normal, -1);
	return (normal);
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

void	intersect_object(t_ray ray, t_object *obj, double *t,
	t_object *origin_obj)
{
	t[0] = -1.0;
	t[1] = -1.0;
	// (void)origin_obj;
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

double	vector_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

bool is_in_shadow(t_comps *closest, t_light light, t_object *objects,
	t_vec3 normal)
{
	t_object	*obj;
	t_ray		shadow_ray;
	double		light_distance;
	double		t[2];

	(void)normal;
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
	// color = add_colors(color, set_color(data->amblight.color));
	color = multiply_color(color, data->light.brightness);
	light = normalize_vector(subtract_coords(data->light.position,
				closest->over_point));
	ambient = multiply_color(color, data->amblight.ratio);
	light_dot_normal = dot_product(light, closest->normalv);
	if (light_dot_normal < 0
		|| is_in_shadow(closest, data->light, data->objects, closest->normalv))
		return (set_to_range_color(ambient));
	return (set_to_range_color(get_diffuse(ambient, *closest, *data,
				(t_color_data){color, light, light_dot_normal})));
}

t_vec3	get_intersection_point(t_ray ray, double t)
{
	t_vec3	intersection_point;

	intersection_point = (t_vec3){ray.origin.x + ray.direction.x * t,
		ray.origin.y + ray.direction.y * t,
		ray.origin.z + ray.direction.z * t};
	return (intersection_point);
}

t_coords	add_coords(t_coords a, t_coords b)
{
	t_coords	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_comps	prepare_comps(t_inter inter, t_ray ray)
{
	t_comps		computations;

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

bool	intersection_obj(t_object *object, t_ray *ray,
	t_inter_list **inter_list)
{
	t_object	*cur;
	bool		hit;
	bool		last_hit;
	double		t[2];

	cur = object;
	hit = false;
	while (cur != NULL)
	{
		if (cur->type == SPHERE)
			last_hit = hit_sphere(cur->object, ray_transform(*ray,
						get_geo(cur).sphere->inversed_t), t);
		else if (cur->type == PLANE)
			last_hit = hit_plane(ray_transform(*ray,
						get_geo(cur).plane->inversed_t), t);
		else if (cur->type == CYLINDER)
			last_hit = hit_cylinder(cur->object, ray_transform(*ray,
						get_geo(cur).cylinder->inversed_t), t);
		if (last_hit)
		{
			if (t[0] != t[1])
			{
				add_to_list(cur, t[0], inter_list);
				add_to_list(cur, t[1], inter_list);
			}
			else
				add_to_list(cur, t[0], inter_list);
			last_hit = false;
			hit = true;
		}
		cur = cur->next;
	}
	return (hit);
}

t_color	trace_ray2(t_data *data, t_ray ray)
{
	t_inter_list	*inter_list;
	t_inter			closest_inter;
	t_comps			computations;

	inter_list = NULL;
	if (!data->objects)
		return ((t_color){0, 0, 0, 1});
	if (!intersection_obj(data->objects, &ray, &inter_list)
		|| !find_closest_inter(&closest_inter, inter_list))
	{
		delete_inter_list(inter_list);
		return ((t_color){0, 0, 0, 1});
	}
	delete_inter_list(inter_list);
	computations = prepare_comps(closest_inter, ray);
	return (get_color(data, &computations));
}

t_ray	ray_for_pixel(t_camera *camera, double pos_x, double pos_y)
{
	double		xoffset;
	double		yoffset;
	t_coords	world;
	t_coords	pixel;
	t_ray		ray;

	xoffset = (pos_x + 0.5) * camera->pixel_size;
	yoffset = (pos_y + 0.5) * camera->pixel_size;
	world = set_coords(camera->half_width - xoffset,
			camera->half_height - yoffset, -1);
	pixel = matrix_multiply_coords(camera->inversed_t, world);
	ray.origin = camera->origin;
	ray.direction = normalize_vector(subtract_coords(pixel, ray.origin));
	return (ray);
}

void	render_scene(t_data *data, t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	ray;

	mlx->win_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	mlx->img_ptr = mlx_new_image(mlx->win_ptr, WIDTH, HEIGHT);
	printf("Rendering...\n");
	y = -1;
	while (++y < data->camera.height_v)
	{
		x = -1;
		while (++x < data->camera.width_v)
		{
			ray = ray_for_pixel(&data->camera, x, y);
			mlx_put_pixel(mlx->img_ptr, x, y,
				t_color_to_int(trace_ray2(data, ray)));
		}
		printf("\rProgress: %.2f%%\r", (float)y / HEIGHT * 100);
	}
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("\e[1;32mRendering done\n\e[0m");
}
