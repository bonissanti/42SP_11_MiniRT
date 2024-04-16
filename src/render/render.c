/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/16 17:35:34 by rseelaen         ###   ########.fr       */
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

t_color	multiply_color(t_color color, double scalar)
{
	t_color	result;

	result.r = color.r * scalar;
	result.g = color.g * scalar;
	result.b = color.b * scalar;
	result.a = 1;
	return (result);
}

t_color	add_colors(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	result.a = 1;
	return (result);
}

t_color	set_to_range_color(t_color color)
{
	t_color	result;

	result.r = fmin(fmax(color.r, 0.0), 1.0);
	result.g = fmin(fmax(color.g, 0.0), 1.0);
	result.b = fmin(fmax(color.b, 0.0), 1.0);
	result.a = 1;
	return (result);
}

t_coords	multiply_vector(t_coords v, double scalar)
{
	t_coords	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
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

bool	is_inside(t_vec3 eyev, t_vec3 *normal)
{
	if (dot_product(eyev, *normal) >= 0)
		return (false);
	normal->x = -normal->x;
	normal->y = -normal->y;
	normal->z = -normal->z;
	return (true);
}

t_color	get_diffuse(t_color ambient, t_comps comps, t_data data, t_color_data c_data)
{
	t_color		diffuse;
	t_color 	specular;
	t_vec3		reflect;
	double		reflect_dot_eye;
	double		factor;

	diffuse = multiply_color(c_data.color, DIFFUSE * c_data.light_dot_normal);
	reflect = reflect_vector(multiply_vector(c_data.light, -1), comps.normalv);
	reflect_dot_eye = dot_product(reflect, comps.eyev);
	if (reflect_dot_eye <= 0)
		return(add_colors(ambient, diffuse));
	else
	{
		factor = pow(reflect_dot_eye, SHININESS);
		specular = multiply_color((t_color){data.light.brightness,
				data.light.brightness, data.light.brightness, 1},
				SPECULAR * factor);
		return(add_colors(add_colors(ambient, diffuse), specular));
	}
}

t_coords	add_tuple(t_coords a, t_coords b)
{
	t_coords	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_coords	multiply_tuple(t_coords a, double scalar)
{
	t_coords	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

t_coords	subtract_tuple(t_coords a, t_coords b)
{
	t_coords	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

void	intersect_object(t_ray ray, t_object *object, double *t,
	t_object *origin_obj)
{
	t[0] = -1.0;
	t[1] = -1.0;
	if (object == origin_obj)
		return ;
	if (object->type == SPHERE)	
		hit_sphere((t_sphere *)object->object, ray, t);
	else if (object->type == PLANE)
		hit_plane(ray, t);
	else if (object->type == CYLINDER)
		hit_cylinder((t_cylinder *)object->object, ray, t);
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

	shadow_ray.origin = add_tuple(closest->point, multiply_tuple(normal,
				EPSILON));
	shadow_ray.direction = normalize_vector(subtract_tuple(light.position,
				shadow_ray.origin));
	light_distance = vector_length(subtract_tuple(light.position,
				shadow_ray.origin));
	obj = objects;
	while (obj != NULL)
	{
		intersect_object(ray_transform(shadow_ray,
				get_geo(obj).sphere->inversed_t), obj, t, closest->object);
		if ((t[0] > EPSILON && t[0] < light_distance)
			|| (t[1] > EPSILON && t[1] < light_distance))
			return (true);
		obj = obj->next;
	}
	return (false);
}

t_color	normalize_color(t_color color) //Option to set_to_range_color
{
	double	max;
	double	factor;

	max = fmax(fmax(color.r, color.g), color.b);
	if (max > 1)
	{
		factor = 1 / max;
		color.r *= factor;
		color.g *= factor;
		color.b *= factor;
	}
	return (color);
}

t_color	get_color(t_data *data, t_comps *closest)
{
	t_color		color;
	t_color		ambient;
	t_sphere	*sphere;
	t_vec3		light;
	double		light_dot_normal;

	sphere = (t_sphere *)closest->object->object;
	color = multiply_color((t_color){sphere->color[0], sphere->color[1],
			sphere->color[2], 1}, data->light.brightness);
	light = normalize_vector(subtract_coords(data->light.position,
				closest->point));
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

t_vec3	get_normal(t_vec3 point, t_vec3 center)
{
	t_vec3	normal;

	normal = subtract_vector(point, center);
	return (normalize_vector(normal));
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

t_vec3	plane_normal(t_plane *plane)
{
	t_vec3		obj_normal;
	t_vec3		normal;

	obj_normal = plane->vector;
	normal = matrix_multiply_coords(transpose_matrix(&plane->inversed_t),
			obj_normal);
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
		normal = plane_normal(geo.plane);
	else
		normal = subtract_vector(point, geo.plane->position);
	return (normalize_vector(normal));
}

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
	t_sphere	*sphere;

	sphere = (t_sphere *)inter.object->object;
	computations.t = inter.t;
	computations.point = get_intersection_point(ray_transform(ray,
				sphere->inversed_t), inter.t);
	computations.over_point = add_coords(computations.point,
			multiply_vector(inter.normal, EPSILON));
	computations.eyev = normalize_vector(multiply_vector(ray.direction, -1));
	computations.normalv = get_normal_generic(inter.object, computations.point);
	is_inside(computations.eyev, &computations.normalv);
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
	hit = false;
	while (cur != NULL)
	{
		if (cur->type == SPHERE)
		{
			temp_ray = ray_transform(*ray, get_geo(cur).sphere->inversed_t);
			last_hit = hit_sphere(cur->object, temp_ray, t);
		}
		else if (cur->type == PLANE)
		{
			temp_ray = ray_transform(*ray, get_geo(cur).plane->inversed_t);
			last_hit = hit_plane(temp_ray, t);
		}
		else if (cur->type == CYLINDER)
		{
			temp_ray = ray_transform(*ray, get_geo(cur).cylinder->inversed_t);
			last_hit = hit_cylinder(cur->object, temp_ray, t);
		}
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

static void	key_hook(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (mlx_is_key_down(mlx->win_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->win_ptr);
}

void	render_scene(t_data *data, t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	ray;

	mlx->win_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	mlx->img_ptr = mlx_new_image(mlx->win_ptr, WIDTH, HEIGHT);
	y = -1;
	for (t_object *obj = data->objects; obj; obj = obj->next)
	{
		if (obj->type == SPHERE)
			printf("Color: %f %f %f\n", ((t_sphere *)obj->object)->color[0],
				((t_sphere *)obj->object)->color[1],
				((t_sphere *)obj->object)->color[2]);
		else if (obj->type == PLANE)
			printf("Color: %f %f %f\n", ((t_plane *)obj->object)->color[0],
				((t_plane *)obj->object)->color[1],
				((t_plane *)obj->object)->color[2]);
		else if (obj->type == CYLINDER)
			printf("Cylinder\n");
	}
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
	mlx_loop_hook(mlx->win_ptr, key_hook, mlx);
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("Rendering done\n");
}
