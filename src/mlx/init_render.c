#include "../../include/minirt.h"


void	render_scene(t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	ray

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray 
		}
	}
}

// degrade do azul claro para o branco
// void	render_scene(t_mlx *mlx)
// {
// 	int	x;
// 	int	y;
//
// 	y = -1;
// 	while (++y < HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			//ray_for_pixel() 
// 			double	ratio = (double)y / HEIGHT;
//
// 			int start_red = 161, start_green = 199, start_blue = 255;
// 			int	end_red = 255, end_green = 255, end_blue = 255;
//
// 			int red = (end_red - start_red) * ratio + start_red;
// 			int green = (end_green - start_green) * ratio + start_green;
// 			int blue = (end_blue - start_blue) * ratio + start_blue;
//
// 			int color = (red << 24) + (green << 16) + (blue << 8) + 255;
//
// 			mlx_put_pixel(mlx->img_ptr, x , y, color);
// 		}
// 	}
// }

void	create_mlx_window(t_mlx *mlx)
{
	mlx->win_ptr = NULL;
	mlx->img_ptr = NULL;
	mlx->width = WIDTH;
	mlx->height = HEIGHT;

	mlx->win_ptr = mlx_init(mlx->width, mlx->height, TITLE, false);
	if (!mlx->win_ptr)
		return ;
	mlx->img_ptr = mlx_new_image(mlx->win_ptr, mlx->width, mlx->height);
	if (!mlx->img_ptr)
	{
		free(mlx->img_ptr);
		return ;
	}
	render_scene(mlx);
	// mlx_key_hook(mlx->win_ptr, exit_key, mlx);
	
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	// mlx_loop_hook(mlx->win_ptr, NULL, mlx);
	mlx_loop(mlx->win_ptr);
	// free mlx
}

