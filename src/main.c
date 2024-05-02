/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:39 by brunrodr          #+#    #+#             */
/*   Updated: 2024/05/01 23:27:50 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	key_hook(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx_is_key_down(mlx->win_ptr, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(mlx->win_ptr, mlx->img_ptr);
		mlx_close_window(mlx->win_ptr);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_mlx	mlx;

	init_structs(&data);
	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	else if (valid_file(argv[1], &data) == ERROR)
		return (1);
	else if (parse_lines(&data) == ERROR)
		return (1);
	mlx.win_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	mlx.img_ptr = mlx_new_image(mlx.win_ptr, WIDTH, HEIGHT);
	render_scene(&data, &mlx);
	mlx_loop_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_loop(mlx.win_ptr);
	mlx_terminate(mlx.win_ptr);
	free_objects(data.objects);
	return (0);
}
