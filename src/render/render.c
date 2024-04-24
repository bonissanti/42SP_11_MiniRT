/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/23 22:01:28 by renato           ###   ########.fr       */
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

t_vec3	is_inside(t_vec3 eyev, t_vec3 normal)
{

	if (dot_product(eyev, normal) < 0)
		return (multiply_vector(normal, -1));
	return (normal);
}

double	vector_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
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
		printf("Progress: %.2f%%\r", (float)y / HEIGHT * 100);
	}
	mlx_put_string(mlx->win_ptr, "Rendering done", 10, 10);
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("Rendering done\n");
}
