/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/13 20:38:29 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	matrix_multiply_vector(const t_matrix *m, const t_vec3 *point)
{
	t_vec3	result;

	result.x = m->matrix[0][0] * point->x + m->matrix[0][1] * point->y
			+ m->matrix[0][2] * point->z;
	result.y = m->matrix[1][0] * point->x + m->matrix[1][1] * point->y
			+ m->matrix[1][2] * point->z;
	result.z = m->matrix[2][0] * point->x + m->matrix[2][1] * point->y
			+ m->matrix[2][2] * point->z;
	return (result);
}

t_ray	ray_transform(t_ray ray, t_matrix *matrix)
{
	t_ray	transformed_ray;

	transformed_ray.origin = matrix_multiply_point(*matrix, ray.origin);
	transformed_ray.direction = matrix_multiply_vector(matrix, &ray.direction);
	return (transformed_ray);
}

t_geo_u get_geo(t_object *object)
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

t_vec3	subtract_tuple(t_coords a, t_coords b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	add_tuple(t_coords a, t_coords b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

double	length_vector(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double intersect_object(t_ray ray, t_object *object)
{
	double t = -1.0;
    if (object->type == SPHERE)	
		hit_sphere((t_sphere *)object->object, &ray, &t);
    // else if (object->type == PLANE)
    //     return intersect_plane(ray, *(t_plane *)object->object);
	// else if (object->type == CYLINDER)
    //     return intersect_cylinder(ray, *(t_cylinder *)object->object);
    return (t);
}

t_coords	multiply_tuple(t_coords a, double b)
{
	t_coords	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

bool is_in_shadow(t_inter *closest, t_light light, t_object *objects, t_vec3 normal)
{
	t_ray	shadow_ray;
	double	light_distance;

	shadow_ray.origin = add_tuple(closest->point, multiply_tuple(normal,
				EPSILON));
	// printf("shadow_ray.origin: %f %f %f\n", shadow_ray.origin.x, shadow_ray.origin.y, shadow_ray.origin.z);
	shadow_ray.direction = normalize_vector(subtract_tuple(light.position,
				shadow_ray.origin));
	light_distance = length_vector(subtract_tuple(light.position,
				shadow_ray.origin));
	for (t_object *obj = objects; obj != NULL; obj = obj->next)
	{
		if (closest->object == obj)
			continue ;
		double t = intersect_object(ray_transform(shadow_ray,
				&get_geo(obj).sphere->inversed_t), obj);
		if (t > EPSILON && t < light_distance)
			return (true);
	}
	return (false);
}

t_vec3	get_normal(t_coords point, t_object object)
{
	t_vec3	normal;
	t_geo_u	geo;

	normal = (t_vec3){ 0,0,0 };
	geo = get_geo(&object);
	if (object.type == SPHERE)
		normal = subtract_tuple(point, geo.sphere->position);
	// else if (object.type == PLANE)
	// 	normal = (t_vec3){0, 1, 0};
	// else if (object.type == CYLINDER)
	// 	normal = subtract_tuple(point, geo.cylinder->position);
	return (normalize_vector(normal));
}

t_color	process_intersection(t_data *data, t_inter *closest, t_ray *ray)
{
	t_color		color;
	t_sphere	*sphere;
	double		intensity;
	t_vec3		normal;
	t_vec3		light;

	(void)ray;
	sphere = (t_sphere *)closest->object->object;
	normal = get_normal(closest->point, *closest->object);
	light = subtract_coords(data->light.position,
			(t_coords){closest->point.x, closest->point.y, closest->point.z});
	light = normalize_vector(light);
	if (is_in_shadow(closest, data->light, data->objects, normal))
		intensity = data->amblight.ratio;
	else
		intensity = fmin(fmax(dot_product(normal, light), 0.0)
				+ data->amblight.ratio, 1.0);
	color.r = (sphere->color[0] / 255.0) * intensity;
	color.g = (sphere->color[1] / 255.0) * intensity;
	color.b = (sphere->color[2] / 255.0) * intensity;
	color.a = 1;
	return (color);
}

t_vec3	get_intersection_point(t_ray ray, double t)
{
	t_vec3	intersection_point;

	intersection_point = (t_vec3){
		ray.origin.x + ray.direction.x * t,
		ray.origin.y + ray.direction.y * t,
		ray.origin.z + ray.direction.z * t
	};
	return (intersection_point);
}

bool intersection_obj(t_object *object, t_ray *ray, t_inter_list **inter_list)
{
	t_object	*cur;
	bool		hit;
	bool		cur_hit;
	double		t_temp;
	t_ray		temp_ray;

	t_temp = 0.0;
	hit = false;
	cur = object;
	while (cur)
	{
		cur_hit = false;
		if (cur->type == SPHERE)
		{
			temp_ray = ray_transform(*ray, &get_geo(cur).sphere->inversed_t);
			cur_hit = hit_sphere(cur->object, &temp_ray, &t_temp);
		}
		if (cur_hit == true)
		{
			t_vec3 point = add_tuple(ray->origin, multiply_tuple(ray->direction, t_temp));
			// printf("temp_ray.direction: %f %f %f\n", temp_ray.direction.x, temp_ray.direction.y, temp_ray.direction.z);
			// printf("point: %f %f %f\n", point.x, point.y, point.z);
			add_inter_list_back(inter_list, (t_inter){t_temp, point,
				get_normal(point, *cur), cur});
			hit = true;
		}
		cur = cur->next;
	}
	return (hit);
}

t_color	trace_ray(t_data *data, t_ray ray)
{
	t_inter			closest_found;
	t_inter_list	*inter_list;	
	t_color			color;
	bool			hit;

	ray.closest_t = INFINITY;
	inter_list = NULL;
	// hit = intersection_bvh(data->bvh_root, &inter_list, ray);
	hit = intersection_obj(data->objects, &ray, &inter_list);
	if (!hit || !find_closest_inter(&closest_found, &inter_list))
	{
		delete_inter_list(inter_list);
		return ((t_color){0.68, 0.85, 0.9, 1});
	}
	color = process_intersection(data, &closest_found, &ray);
	delete_inter_list(inter_list);
	return (color);
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
	world = set_coords(camera->half_width - xoffset, camera->half_height
			- yoffset, -1);
	pixel = matrix_multiply_point(camera->inversed_t, world);
	ray.origin = camera->origin;
	ray.direction = normalize_vector(subtract_coords(pixel, ray.origin));
	ray.closest_t = INFINITY;
	ray.front_t = 0;
	ray.back_t = 0;
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
				t_color_to_int(trace_ray(data, ray)));
		}
	}
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("Rendering done\n");
}
