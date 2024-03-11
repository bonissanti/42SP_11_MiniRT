#include "../../include/minirt.h"

// t_ray	ray_for_pixel(t_data *data, int x, int y)
// {
// 	double		px;
// 	double		py;
// 	t_coords	pixel_transformed;
// 	t_coords	origin_transformed;
// 	t_ray		ray;

// 	px = (2.0 * (x + 0.5) / data->camera.width_v - 1) * data->camera.aspect_ratio * data->camera.half_width;
// 	py = (1 - 2.0 * (y + 0.5) / data->camera.height_v) * data->camera.half_height;
// 	t_coords pixel_world = {px, py, -1};
	
// 	pixel_transformed = matrix_multiply_point(&data->camera.transform, &pixel_world);
// 	origin_transformed = matrix_multiply_point(&data->camera.transform, &(t_coords){0, 0, 0});

// 	t_vec3	direction = {
// 		pixel_transformed.x - origin_transformed.x,
// 		pixel_transformed.y - origin_transformed.y,
// 		pixel_transformed.z - origin_transformed.z
// };
// 	direction = normalize_vector(direction);

// 	ray.origin = origin_transformed;
// 	ray.direction = direction;
// 	return (ray);
// }

// void	render_scene(t_data *data, t_mlx *mlx)
// {
// 	int		x;
// 	int		y;
// 	t_ray	ray;
// 	t_color	pixel_color;

// 	y = -1;
// 	while (++y < data->camera.height_v)
// 	{
// 		x = -1;
// 		while (++x < data->camera.width_v)
// 		{
// 			ray = ray_for_pixel(data, x, y);
// 			// pixel_color = trace_ray(ray, data);
// 			// mlx_put_pixel(mlx->img_ptr, x, y, );
// 		}
// 	}
// 	// mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
// }
