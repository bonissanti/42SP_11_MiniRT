#include "../../include/minirt.h"

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
	// mlx_key_hook(mlx->win_ptr, exit_key, mlx);
	mlx_loop_hook(mlx->win_ptr, NULL, mlx);
	mlx_image_to_window(mlx->win_ptr, mlx->img_ptr, 0, 0);
	// mlx_loop(mlx->win_ptr);
	// free mlx
}

