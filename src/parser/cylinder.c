/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:47 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/23 16:36:39 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_cylinder *new_cylinder)
{
	char	**split;

	split = ft_split(line, ',');
	new_cylinder->position.x = ft_atod(split[0]);
	new_cylinder->position.y = ft_atod(split[1]);
	new_cylinder->position.z = ft_atod(split[2]);
	free_array(split);
	return (OK);
}

static int	fill_colors(char *line, t_cylinder *new_cylinder)
{
	char	**split_line;

	split_line = ft_split(line, ',');
	new_cylinder->color[0] = ft_atod(split_line[0]) / 255;
	new_cylinder->color[1] = ft_atod(split_line[1]) / 255;
	new_cylinder->color[2] = ft_atod(split_line[2]) / 255;
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

static void	fill_cylinder_data(t_cylinder *cyl, char **tokens)
{
	fill_coordinates(tokens[0], cyl);
	fill_vector(tokens[1], cyl);
	cyl->diameter = ft_atod(tokens[2]);
	cyl->height = ft_atod(tokens[3]);
	cyl->max = cyl->height / 2;
	cyl->min = -(cyl->height / 2);
	cyl->transform = transform_cylinder(cyl->position,
			cyl->diameter / 2, cyl->vector);
	invert_matrix(&cyl->transform, &cyl->inversed_t);
	cyl->position = (t_coords){0, 0, 0};
	cyl->vector = (t_coords){0, 1, 0};
	print_matrix(cyl->transform);
	// print_matrix(cyl->inversed_t);
	printf("\n");
	fill_colors(tokens[4], cyl);
}

int	analyze_cylinder(char *line, t_data *data)
{
	char		**token;
	t_cylinder	*new_cylinder;

	token = ft_split_space(line);
	if (count_token(token, 5, "Cylinder has wrong number of arguments"))
		return (ERROR);
	new_cylinder = malloc(sizeof(t_cylinder));
	if (set_coordinates(token[0]) == ERROR || set_vector_3d(token[1]) == ERROR
		|| is_number(token[2]) == ERROR || is_number(token[3]) == ERROR
		|| set_colors(token[4]) == ERROR || !new_cylinder)
	{
		free_array(token);
		return (ERROR);
	}
	fill_cylinder_data(new_cylinder, token);
	if (add_objects(data, new_cylinder, CYLINDER) == ERROR)
	{
		free(new_cylinder);
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}

