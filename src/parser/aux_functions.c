/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:25:16 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	set_coordinates(char *coord_line)
{
	char	**coord_split;

	coord_split = ft_split(coord_line, ',');
	if (count_token(coord_split, 3, "Incorrect number of coordinates, "
			"e.g [-10.0,0,0]\n"))
		return (ERROR);
	if (validate_numbers_dot(coord_split) == ERROR)
	{
		free_array(coord_split);
		return (ERROR);
	}
	free_array(coord_split);
	return (OK);
}

int	set_range(char *line, int min, int max)
{
	double	value;

	if (is_number(line) == ERROR)
		return (ERROR);
	value = ft_atod(line);
	if (value < min || value > max)
		return (ERROR);
	return (OK);
}

static int	validate_colors(char **color_str)
{
	int	i;
	int	color;

	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(color_str[i]);
		if (color < 0 || color > 255)
			return (print_error("[A] Color out of range [0, 255]"));
	}
	return (OK);
}

int	set_colors(char *color_line)
{
	char	**color_split;

	color_split = ft_split(color_line, ',');
	if (count_token(color_split, 3,
			"[A] Incorrect number of RGB componentes\n"))
		return (ERROR);
	if (validate_colors(color_split) != 0)
	{
		free_array(color_split);
		return (ERROR);
	}
	free_array(color_split);
	return (OK);
}

int	validate_numbers_dot(char **str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (is_number(str[i]) == ERROR)
			return (print_error("Invalid number"));
	}
	return (OK);
}
