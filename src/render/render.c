/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/15 18:24:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

// t_color	get_color(t_data *data, t_inter *closest, t_ray *ray)
// {
// 	t_color		color;
// 	t_sphere	*sphere;
// 	double		intensity;
// 	t_vec3		normal;
// 	t_vec3		light;

// 	(void)ray;
// 	sphere = (t_sphere *)closest->object->object;
// 	normal = normalize_vector(subtract_coords((t_coords){closest->point.x,
// 				closest->point.y, closest->point.z}, sphere->position));
// 	light = subtract_coords(data->light.position,
// 			(t_coords){closest->point.x, closest->point.y, closest->point.z});
// 	light = normalize_vector(light);
// 	intensity = fmin(fmax(dot_product(normal, light), 0.0)
// 			+ data->amblight.ratio, 1.0);
// 	color.r = (sphere->color[0] / 255.0) * intensity;
// 	color.g = (sphere->color[1] / 255.0) * intensity;
// 	color.b = (sphere->color[2] / 255.0) * intensity;
// 	color.a = 1;
// 	return (color);
// }

t_color	get_color(t_data *data, t_comps *closest)
{
	t_color		color;
	t_sphere	*sphere;
	double		intensity;
	t_vec3		light;


	sphere = (t_sphere *)closest->object->object;
	light = subtract_coords(data->light.position, closest->point);
	light = normalize_vector(light);
	// intensity = fmin(fmax(dot_product(closest->normalv, light), 0.0)
	// 		+ data->amblight.ratio, 1.0);
	intensity = fmax(dot_product(closest->normalv, light), 0.0)
			+ data->amblight.ratio;
	if (intensity > 1)
		return ((t_color){1, 1, 1, 1});
	color.r = (sphere->color[0] / 255.0) * intensitsy;
	color.g = (sphere->color[1] / 255.0) * intensity;
	color.b = (sphere->color[2] / 255.0) * intensity;
	color.a = 1;
	// printf("color: %f %f %f\n", color.r, color.g, color.b);
	return (color);
}

t_vec3	get_intersection_point(t_ray ray, double t)
{
	t_vec3	intersection_point;

	intersection_point = (t_vec3){ray.origin.x + ray.direction.x * t,
		ray.origin.y + ray.direction.y * t,
		ray.origin.z + ray.direction.z * t};
	return (intersection_point);
}

t_vec3	get_normal(t_vec3 point, t_vec3 center)
{
	t_vec3	normal;

	normal = subtract_vector(point, center);
	return (normalize_vector(normal));
}

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

t_vec3	sphere_normal(t_vec3 point, t_sphere *sphere)
{
	t_coords	obj_point;
	t_vec3		obj_normal;
	t_vec3		normal;

	obj_point = matrix_multiply_coords(sphere->inversed_t, point); 
	obj_normal = subtract_coords(obj_point, (t_coords){0, 0, 0});
	normal = matrix_multiply_coords(transpose_matrix(&sphere->inversed_t), obj_normal);
	return (normal);
}

t_vec3	get_normal_generic(t_object *obj, t_vec3 point)
{
	t_vec3	normal;
	t_geo_u	geo;

	geo = get_geo(obj);
	if (geo.sphere)
		normal = sphere_normal(point, geo.sphere);
	else if (geo.cylinder)
		normal = subtract_vector(point, geo.cylinder->position);
	else
		normal = subtract_vector(point, geo.plane->position);
	return (normalize_vector(normal));
}


// bool intersection_obj(t_object *object, t_ray *ray, t_inter_list **inter_list)
// {
// 	t_object	*cur;
// 	bool		hit;
// 	t_inter		xs;
// 	// t_geo_u		geo;
// 	t_ray		temp_ray;
//
// 	xs.t[0] = 0.0;
// 	xs.t[1] = 0.0;
// 	hit = false;
// 	cur = object;
// 	while (cur)
// 	{
// 		// geo = 
// 		if (cur->type == SPHERE)
// 		{
// 			temp_ray = ray_transform(*ray, get_geo(cur).sphere->inversed_t);
// 			hit |= hit_sphere(cur->object, temp_ray, &xs);
// 		}
// 		if (hit == true)
// 		{
// 			t_vec3 point = get_intersection_point(temp_ray, xs.t[0]);
// 			add_inter_list_back(inter_list, (t_inter){xs.t[0], point,
// 				get_normal(point, (t_vec3){get_geo(cur).sphere->position.x,
// 				get_geo(cur).sphere->position.y, get_geo(cur).sphere->position.z}), cur});
// 			hit = true;
// 		}
// 		cur = cur->next;
// 	}
// 	return (hit);
// }


// void add_intersection_if_valid(t_object *obj, t_ray ray, double t, t_inter_list **inter_list) {
//     if (t > EPSILON && t < INFINITY) {
//         t_vec3 point = get_intersection_point(ray, t);
//         t_vec3 normal = get_normal_generic(obj, point); // Assume-se que essa função já esteja ajustada
//         // Adiciona a interseção à lista
//         add_inter_list_back(inter_list, (t_inter){t, point, normal, obj});
//     }
// }

// void	add_intersection_if_valid(t_object *obj, t_ray ray, double t, t_inter_list **inter_list)
// {
// 	t_vec3	point;
// 	t_vec3	normal;
//
// 	if (t > EPSILON && t < INFINITY)
// 	{
// 		point = get_intersection_point(ray, t);
// 		normal = get_normal_generic(obj, point);
// 		add_inter_list_back(inter_list, obj, t) ;
// 	}
// }

// bool intersection_obj(t_object *object, t_ray *ray, t_inter_list **inter_list)
// {
// 	bool		hit;
// 	t_ray		temp_ray;
// 	t_object	*cur;
// 	t_geo_u		geo;
// 	t_inter		xs;
//
// 	hit = false;
// 	cur = object;
// 	while (cur)
// 	{
// 		geo = get_geo(object);
// 		if (cur->type == SPHERE)
// 		{
// 			temp_ray = ray_transform(*ray, geo.sphere->inversed_t);
// 			hit = hit_sphere(geo.sphere, *ray, &xs);
// 		}
// 		if (hit)
// 		{
// 			add_intersection_if_valid(cur, *ray, xs.t[0], inter_list);
// 			add_intersection_if_valid(cur, *ray, xs.t[1], inter_list);
// 		}
// 		cur = cur->next;
// 	}
// 	return (hit);
// }

t_coords	multiply_vector(t_coords v, double scalar)
{
	t_coords	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_coords	add_coords(t_coords a, t_coords b)
{
	t_coords	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	reflect_vector(t_vec3 in, t_vec3 normal)
{
	return (subtract_vector(in, multiply_vector(normal,
				2 * dot_product(in, normal))));
}

t_comps	prepare_comps(t_inter inter, t_ray ray)
{
	t_comps		computations;
	t_sphere	*sphere;

	sphere = (t_sphere *)inter.object->object;
	computations.t = inter.t;
	computations.point = get_intersection_point(ray_transform(ray,
				sphere->inversed_t), inter.t);
	computations.over_point = add_coords(computations.point,
			multiply_vector(inter.normal, EPSILON));
	computations.eyev = normalize_vector(multiply_vector(ray.direction, -1));
	computations.normalv = get_normal_generic(inter.object, computations.point);
	computations.reflectv = reflect_vector(ray.direction, computations.normalv);
	computations.object = inter.object;
	return (computations);
}

void	add_to_list(t_object *cur, double t,
	t_inter_list **inter_list)
{
	add_inter_list_back(inter_list, (t_inter){t, (t_vec3){0, 0, 0},
		(t_vec3){0, 0, 0}, cur});
}

bool	intersection_obj(t_object *object, t_ray *ray,
	t_inter_list **inter_list)
{
	t_object	*cur;
	bool		hit;
	bool		last_hit;
	t_ray		temp_ray;
	double		t[2];

	cur = object;
	while (cur != NULL)
	{
		if (cur->type == SPHERE)
		{
			temp_ray = ray_transform(*ray, get_geo(cur).sphere->inversed_t);
			last_hit = hit_sphere(cur->object, temp_ray, t);
		}
		// else if (cur->type == PLANE)
		// {
		// 	temp_ray = ray_transform(*ray, get_geo(cur).plane->inversed_t);
		// 	last_hit = hit_sphere(cur->object, temp_ray, t);
		// }
		// else if (cur->type == CYLINDER)
		// {
		// 	temp_ray = ray_transform(*ray, get_geo(cur).cylinder->inversed_t);
		// 	last_hit = hit_sphere(cur->object, temp_ray, t);
		// }
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
	bool			hit;

	inter_list = NULL;
	if (!data->objects)
		return ((t_color){0, 0, 0, 1});
	hit = intersection_obj(data->objects, &ray, &inter_list);
	if (!hit || !find_closest_inter(&closest_inter, inter_list))
	{
		delete_inter_list(inter_list);
		return ((t_color){0, 0, 0, 1});
	}
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

int	t_color_to_int(t_color color)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (int)(color.r * 255.999);
	green = (int)(color.g * 255.999);
	blue = (int)(color.b * 255.999);
	alpha = (int)(color.a * 255.999);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

void	render_scene(t_data *data, t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	ray;

	mlx->win_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	mlx->img_ptr = mlx_new_image(mlx->win_ptr, WIDTH, HEIGHT);
	// data->bvh_root = create_bvh(&data->objects);
	// traverseBVH(data->bvh_root, 0);
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
	}
	// ray = ray_for_pixel(&data->camera, WIDTH / 2, HEIGHT / 2);
	// mlx_put_pixel(mlx->img_ptr, WIDTH / 2, HEIGHT / 2,
	// 			t_color_to_int(trace_ray2(data, ray)));
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("Rendering done\n");
}
