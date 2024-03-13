/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:47 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:42:04 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_cylinder *new_cylinder)
{
	char **split;

	split = ft_split(line, ',');
	new_cylinder->position.x = ft_atod(split[0]);
	new_cylinder->position.y = ft_atod(split[1]);
	new_cylinder->position.z = ft_atod(split[2]);
	free_array(split);
	return (OK);
}

static int	fill_colors(char *line, t_cylinder *new_cylinder)
{
	char **split_line;

	split_line = ft_split(line, ',');
	new_cylinder->color[0] = ft_atod(split_line[0]);
	new_cylinder->color[1] = ft_atod(split_line[1]);
	new_cylinder->color[2] = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

static int	fill_vector(char *line, t_cylinder *new_cylinder)
{
	double	x;
	double	y;
	double	z;
	double	magnitude;
	char	**vector_str;

	vector_str = ft_split(line, ',');
	x = ft_atod(vector_str[0]);
	y = ft_atod(vector_str[1]);
	z = ft_atod(vector_str[2]);
	magnitude = sqrt(x * x + y * y + z * z);
	new_cylinder->vector.x = x / magnitude;
	new_cylinder->vector.y = y / magnitude;
	new_cylinder->vector.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}

int	analyze_cylinder(char *line, t_data *data)
{
	char	**token;
	t_cylinder	*new_cylinder;

	token = ft_split_space(line);
	if (count_token(token, 5, "Cylinder has wrong number of arguments"))
		return (ERROR);
	// verifica valores
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}

	if (set_vector_3d(token[1]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}

	if (is_number(token[2]) == ERROR)
	{
		free_array(token);
		return (print_error("[cy] Invalid diameter"));
	}
	if (is_number(token[3]) == ERROR)
	{
		free_array(token);
		return (print_error("[cy] Invalid height"));
	}
	if (set_colors(token[4]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}

	// se ok, cria um objeto, insere os valores e adiciona a lista
	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_cylinder)
	{
		free_array(token);
		return (ERROR);
	}
	fill_coordinates(token[0], new_cylinder);
	fill_vector(token[1], new_cylinder);
	new_cylinder->diameter = ft_atod(token[2]);
	new_cylinder->height = ft_atod(token[3]);
	new_cylinder->max = new_cylinder->height / 2;
	new_cylinder->min = new_cylinder->height / 2;
	fill_colors(token[4], new_cylinder);
	
	if (add_objects(data, new_cylinder, CYLINDER) == ERROR)
	{
		free(new_cylinder);
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}
