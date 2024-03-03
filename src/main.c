/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:39 by brunrodr          #+#    #+#             */
/*   Updated: 2024/02/21 11:16:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int main(int argc, char **argv) 
{
	t_data	data;
	t_mlx	mlx;

	init_structs(&data);
	if (argc != 2) 
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	else if (valid_file(argv[1], &data))
		return (1);
	else if (parse_lines(&data))
		return (1);
	run_render(&mlx);
	return (0);
}
