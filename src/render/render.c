/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/21 19:15:23 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	process_intersection(t_data *data, t_inter *closest, t_ray *ray)
{
	t_color		color;
	t_sphere	*sphere;
	double		intensity;
	t_vec3		normal;
	t_vec3		light;

	(void)ray;
	sphere = (t_sphere*)closest->object->object;
	normal = normalize_vector(subtract_coords((t_coords){closest->point.x,
				closest->point.y, closest->point.z}, sphere->position));
	light = subtract_coords(data->light.position,
			(t_coords){closest->point.x, closest->point.y, closest->point.z});
	light = normalize_vector(light);
	intensity = dot_product(normal, light);
	if (intensity < 0)
		intensity = 0.01;
	color.r = (sphere->color[0] / 255.0) * (intensity + data->amblight.ratio); //remove amblight.ratio
	color.g = (sphere->color[1] / 255.0) * (intensity + data->amblight.ratio);
	color.b = (sphere->color[2] / 255.0) * (intensity + data->amblight.ratio);
	color.a = 1;
	return (color);
}

t_color	trace_ray(t_data *data, t_ray ray)
{
	t_inter			closest_found;
	t_inter_list	*inter_list;
	t_color			color;
	bool			hit;

	ray.closest_t = INFINITY;
	inter_list = NULL;
	hit = intersection_bvh(data->bvh_root, &inter_list, ray);
	if (!hit || !find_closest_inter(&closest_found, inter_list))
	{
		delete_inter_list(inter_list);
		return ((t_color){0.68, 0.85, 0.9, 1});
	}
	color = process_intersection(data, &closest_found, &ray);
	delete_inter_list(inter_list);
	return (color);
}

t_ray	ray_for_pixel(t_camera *camera, int pos_x, int pos_y)
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
	#ifndef TEST
		print_matrix(&camera->inversed_t);	
	#endif
	ray.origin = matrix_multiply_point(&camera->inversed_t, &((t_coords){0, 0, 0}));
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
	data->bvh_root = create_bvh(&data->objects);
	traverseBVH(data->bvh_root, 0);
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
