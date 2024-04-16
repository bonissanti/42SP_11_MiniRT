/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/15 14:25:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_sphere *new_sphere)
{
	char	**split;

	split = ft_split(line, ',');
	new_sphere->position.x = ft_atod(split[0]) / 1.5;
	new_sphere->position.y = ft_atod(split[1]) / 1.5;
	new_sphere->position.z = ft_atod(split[2]) / 1.5;
	free_array(split);
	return (OK);
}

static int	fill_colors(char *line, t_sphere *new_sphere)
{
	char	**split_line;

	split_line = ft_split(line, ',');
	new_sphere->color[0] = ft_atod(split_line[0]);
	new_sphere->color[1] = ft_atod(split_line[1]);
	new_sphere->color[2] = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

static void	fill_sphere_data(t_sphere *sphere, char **tokens)
{
	sphere->diameter = ft_atod(tokens[1]) / 2;
	fill_coordinates(tokens[0], sphere);
	sphere->transform = transform_sphere(sphere->position,
			sphere->diameter);
	invert_matrix(&sphere->transform, &sphere->inversed_t);
	fill_colors(tokens[2], sphere);

}

int	analyze_sphere(char *line, t_data *data)
{
	char		**token;
	t_sphere	*new_sphere = NULL;

	token = ft_split_space(line);
	if (count_token(token, 3, "[sp] Sphere has wrong number of arguments\n"))
		return (ERROR);
	new_sphere = malloc(sizeof(t_sphere));
	if (set_coordinates(token[0]) == ERROR || is_number(token[1]) == ERROR
		|| set_colors(token[2]) == ERROR || !new_sphere)
	{
		free_array(token);
		return (ERROR);
	}
	fill_sphere_data(new_sphere, token);
	if (add_objects(data, new_sphere, SPHERE) == ERROR)
	{
		free(new_sphere);
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}
