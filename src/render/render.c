/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/10 12:31:12 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

t_color	process_intersection(t_data *data, t_inter *closest, t_ray *ray)
{
	t_color		color;
	t_sphere	*sphere;
	double		intensity;
	t_vec3		normal;
	t_vec3		light;

	(void)ray;
	sphere = (t_sphere *)closest->object->object;
	normal = normalize_vector(subtract_coords((t_coords){closest->point.x,
				closest->point.y, closest->point.z}, sphere->position));
	light = subtract_coords(data->light.position,
			(t_coords){closest->point.x, closest->point.y, closest->point.z});
	light = normalize_vector(light);
	intensity = fmin(fmax(dot_product(normal, light), 0.0)
			+ data->amblight.ratio, 1.0);
	color.r = (sphere->color[0] / 255.0) * intensity;
	color.g = (sphere->color[1] / 255.0) * intensity;
	color.b = (sphere->color[2] / 255.0) * intensity;
	color.a = 1;
	return (color);
}

// t_comps	process_intersection()

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

bool intersection_obj(t_object *object, t_ray *ray, t_inter_list **inter_list)
{
	t_object	*cur;
	bool		hit;
	double		t_temp[2] = {INFINITY, INFINITY};
	t_geo_u		geo;
	t_ray		temp_ray;

	hit = false;
	cur = object;
	while (cur)
	{
		geo = get_geo(cur);
		if (cur->type == SPHERE)
		{
			temp_ray = ray_transform(*ray, &geo.sphere->inversed_t);
			hit |= hit_sphere(cur->object, temp_ray, t_temp);
		}
		else if (cur->type == CYLINDER)
		{
			temp_ray = ray_transform(*ray, &geo.cylinder->inversed_t);
			hit |= hit_cylinder(cur->object, temp_ray, t_temp);

		}
		else if (cur->type == PLANE)
		{
			temp_ray = ray_transform(*ray, &geo.plane->inversed_t);
			hit |= hit_plane(temp_ray, t_temp);
		}
		if (hit == true)
		{
			t_vec3 point = get_intersection_point(temp_ray, t_temp[0]);
			t_inter config = config_inter(&geo, point, cur, t_temp);
			add_inter_list_back(inter_list, config);
		}
		cur = cur->next;
	}
	return (hit);
}

bool intersection_obj2(t_object *object, t_ray *ray, t_inter_list **inter_list)
{
	t_object	*cur;
	bool		hit;
	double		t_temp[2] = {INFINITY, INFINITY};
	t_geo_u		geo;
	t_ray		temp_ray;

	hit = false;
	cur = object;
	while (cur)
	{
		geo = get_geo(cur);
		if (cur->type == SPHERE)
		{
			temp_ray = ray_transform(*ray, &geo.sphere->inversed_t);
			hit |= hit_sphere(cur->object, temp_ray, t_temp);
		}
		else if (cur->type == CYLINDER)
		{
			temp_ray = ray_transform(*ray, &geo.cylinder->inversed_t);
			hit |= hit_cylinder(cur->object, temp_ray, t_temp);

		}
		else if (cur->type == PLANE)
		{
			temp_ray = ray_transform(*ray, &geo.plane->inversed_t);
			hit |= hit_plane(temp_ray, t_temp);
		}
		if (hit == true)
		{
			t_vec3 point = get_intersection_point(temp_ray, t_temp[0]);
			t_inter config = config_inter(&geo, point, cur, t_temp);
			add_inter_list_back(inter_list, config);
		}
		cur = cur->next;
	}
	return (hit);
}


//-------------------TESTE-----------------------------------------------
// void teste_inter_point(t_coords point, t_vec3 dir)
// {
// 	t_vec3		result;

// 	result = get_intersection_point((t_ray){0, 0, 0, point, dir, NULL}, 0);
// 	printf("result: %f %f %f\n", result.x, result.y, result.z);
// 	result = get_intersection_point((t_ray){0, 0, 0, point, dir, NULL}, 1);
// 	printf("result: %f %f %f\n", result.x, result.y, result.z);
// 	result = get_intersection_point((t_ray){0, 0, 0, point, dir, NULL}, -1);
// 	printf("result: %f %f %f\n", result.x, result.y, result.z);
// 	result = get_intersection_point((t_ray){0, 0, 0, point, dir, NULL}, 2.5);
// 	printf("result: %f %f %f\n", result.x, result.y, result.z);	
// }

// t_color	trace_ray(t_data *data, t_ray ray)
// {
// 	t_inter			closest_found;
// 	t_inter_list	*inter_list;
// 	bool			hit;
//
// 	// if (!data->bvh_root)
// 	// 	return ((t_color){0.68, 0.85, 0.9, 1}); //in case bvh is null
// 	inter_list = NULL;
// 	hit = intersection_obj(data->objects, &ray, &inter_list);
//
// 	if (!hit || !find_closest_inter(&closest_found, inter_list))
// 	{
// 		delete_inter_list(inter_list);
// 		return ((t_color){0.68, 0.85, 0.9, 1});
// 	}
//
// 	// t_color color = process_intersection(data, &closest_found, &ray);
// 	// delete_inter_list(inter_list);
// 	return((t_color){1, 0, 0, 1});
// }


t_color	trace_ray2(t_data *data, t_ray ray)
{
	t_inter_list	*inter_list;
	// t_comps			computations;
	bool			hit;

	inter_list = NULL;
	if (!data->objects)
		return ((t_color){0, 0, 0, 1});

	hit = intersection_obj2(data->objects, &ray, &inter_list);
	(void)hit;
	// if (!hit || !find_closest_inter2(inter_list))
	// {
	// 	delete_inter_list(inter_list);
	// 	return ((t_color){0, 0, 0, 1});
	// }
	// computations = process_computations()
	return ((t_color){1, 0, 0, 1});
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
	world = set_coords(camera->half_width - xoffset, camera->half_height - yoffset, -1);
	pixel = matrix_multiply_point(&camera->inversed_t, &world);
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
	// teste_inter_point((t_coords){2, 3, 4}, (t_vec3){1, 0, 0});
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
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("Rendering done\n");
}
