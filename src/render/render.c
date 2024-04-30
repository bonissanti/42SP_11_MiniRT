/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:24:33 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/30 12:53:38 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	trace_ray(t_data *data, t_ray ray)
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

/**
 * Function: ray_for_pixel
 * -------------------
 * This function calculates the ray that goes from the camera origin to a
 * specific pixel on the screen. It calculates the world coordinates of the
 * pixel and then transforms it to the camera space. Finally, it returns the
 * ray that goes from the camera origin to the pixel.
 * 
 * Important notes:
 * - xoffset and yoffset are calculated based on the pixel size and the position
 * of the pixel on the screen, they are the center of the pixel.
 * - world is the world coordinates of the pixel, it is calculated based on the
 * position of the pixel on the screen.
 * - pixel is the pixel coordinates in the camera space, it is calculated by
 * multiplying the world coordinates by the inverse of the camera transformation
 * matrix.
 * - ray.origin is the camera origin.
 * - ray.direction is the normalized vector that goes from the camera origin to
 * the object.
 *
 * @return: t_geo_u, aka the object of the union.
 */

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
			mlx_put_pixel(mlx->img_ptr, x, y, t_color_to_int(trace_ray(data,
						ray)));
		}
		printf("Progress: %.2f%%\r", (float)y / HEIGHT * 100);
	}
	mlx_put_string(mlx->win_ptr, "Rendering done", 10, 10);
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	printf("Rendering done\n");
}
