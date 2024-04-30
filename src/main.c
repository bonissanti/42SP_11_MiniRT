/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:39 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/30 12:37:31 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/**
 * Function: key_hook
 * -------------------
 * Detects when the 'ESC' key is pressed and closes the window.
 *
 * This function should be used as a callback in response to keyboard events.
 * It checks if the 'ESC' key (specified by MLX_KEY_ESCAPE) is currently pressed
 * using the mlx_is_key_down function, which detects if a specific key is pressed.
 * If the 'ESC' key is pressed, the function closes the window.
 *
 * @param: param: void because it is a callback function.
 *
 * @return: void
 */

static void	key_hook(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx_is_key_down(mlx->win_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->win_ptr);
}

/**
 * Function: main
 * -------------------
 * The main function of the program. First it initializes the t_data, the
 * master struct that holds all the information about the project. Verify
 * if the number of arguments is correct and if the file is valid. Then it
 * parses the file and renders the scene. It also sets the key_hook function
 * as a callback to the mlx_loop_hook function, which will close the window
 * when the 'ESC' key is pressed. Finally, it loops the mlx window and frees
 * the allocated memory. 
 * 
 * @param: argc: the number of arguments passed to the program.
 * @param: argv: an array of strings containing the arguments passed to the program.
 *
 * @return: 0 if the program runs successfully, 1 if an error occurs.
 */

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
	render_scene(&data, &mlx);
	mlx_loop_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_loop(mlx.win_ptr);
	mlx_terminate(mlx.win_ptr);
	free_objects(data.objects);
	return (0);
}
