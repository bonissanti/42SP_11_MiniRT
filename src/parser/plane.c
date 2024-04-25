/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:40 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:19:51 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_plane *new_plane)
{
	char	**split_line;

	split_line = ft_split(line, ',');
	new_plane->position.x = ft_atod(split_line[0]);
	new_plane->position.y = ft_atod(split_line[1]);
	new_plane->position.z = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

static int	fill_vector(char *line, t_plane *new_plane)
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
	new_plane->vector.x = x / magnitude;
	new_plane->vector.y = y / magnitude;
	new_plane->vector.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}

static int	fill_colors(char *line, t_plane *new_plane)
{
	char	**split_line;

	split_line = ft_split(line, ',');
	new_plane->color[0] = ft_atod(split_line[0]) / 255;
	new_plane->color[1] = ft_atod(split_line[1]) / 255;
	new_plane->color[2] = ft_atod(split_line[2]) / 255;
	free_array(split_line);
	return (OK);
}

static void	fill_plane_data(t_plane *plane, char **tokens)
{
	fill_coordinates(tokens[0], plane);
	fill_vector(tokens[1], plane);
	fill_colors(tokens[2], plane);
	plane->transform = transform_plane(plane->position, plane->vector);
	invert_matrix(&plane->transform, &plane->inversed_t);
	plane->position = (t_coords){0, 0, 0};
}

int	analyze_plane(char *line, t_data *data)
{
	char	**token;
	t_plane	*new_plane;

	token = ft_split_space(line);
	if (count_token(token, 3, "Plane has wrong number of arguments"))
		return (ERROR);
	new_plane = malloc(sizeof(t_plane));
	if (set_coordinates(token[0]) == ERROR || set_vector_3d(token[1]) == ERROR
		|| set_colors(token[2]) == ERROR || !new_plane)
	{
		free_array(token);
		return (ERROR);
	}
	fill_plane_data(new_plane, token);
	if (add_objects(data, new_plane, PLANE) == ERROR)
	{
		free(new_plane);
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}
