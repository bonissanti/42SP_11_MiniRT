#include "../../include/minirt.h"

t_color	trace_ray(t_data *data, t_ray ray)
{
	t_inter			closest_found;
	t_inter_list	*inter_list;
	// t_color			color;
	bool			hit;

	ray.closest_t = INFINITY;
	(void)closest_found;
	(void)inter_list;
	(void)ray;
	(void)hit;
	(void)data;
	// hit = intersection_bvh(data->bvh_root, &inter_list, ray);
	// find_closest_inter(&closest_found, inter_list);
	// if (!hit || find_closest_inter(&closest_found, inter_list))
	// {
	// 	delete_inter_list(inter_list);
	// 	return ((t_color){0, 0, 0, 0});
	// }
	// // color = process_intersection(data, &closest_found, &ray);
	// delete_inter_list(inter_list);
	return ((t_color){0, 0, 0, 5});
}

t_ray	ray_for_pixel(t_camera *camera, int pos_x, int pos_y)
{
	double	xoffset;
	double	yoffset;
	t_coords	world;
	t_coords	pixel;
	t_ray		ray;

	xoffset = (pos_x + 0.5) * camera->pixel_size;
	yoffset = (pos_y + 0.5) * camera->pixel_size;
	world = set_coords(camera->half_width - xoffset, camera->half_height - yoffset, -1);
	pixel = matrix_multiply_point(&camera->inversed_t, &world);
	ray.origin = matrix_multiply_point(&camera->inversed_t, &((t_coords){0, 0, 0}));
	ray.direction = normalize_vector(subtract_coords(pixel, ray.origin));
	return (ray);
}

void	render_scene(t_data *data, t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	pixel_color;

	y = -1;
	(void)mlx;
	while (++y < data->camera.height_v)
	{
		x = -1;
		while (++x < data->camera.width_v)
		{
			ray = ray_for_pixel(&data->camera, x, y);
			pixel_color = trace_ray(data, ray);
			// mlx_put_pixel(mlx->img_ptr, x, y, pixel_color);
		}
	(void)ray;
	}
	// mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
}
