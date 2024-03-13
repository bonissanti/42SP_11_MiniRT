/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:36:37 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_sphere *new_sphere)
{
	char **split;

	split = ft_split(line, ',');
	new_sphere->position.x = ft_atod(split[0]);
	new_sphere->position.y = ft_atod(split[1]);
	new_sphere->position.z = ft_atod(split[2]);
	free_array(split);
	return (OK);
}

static int	fill_colors(char *line, t_sphere *new_sphere)
{
	char **split_line;

	split_line = ft_split(line, ',');
	new_sphere->color[0] = ft_atod(split_line[0]);
	new_sphere->color[1] = ft_atod(split_line[1]);
	new_sphere->color[2] = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

int	analyze_sphere(char *line, t_data *data)
{
	char **token;
	t_sphere *new_sphere;

	token = ft_split_space(line);

	// verifica valores
	if (count_token(token, 3, "[sp] Sphere has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR || is_number(token[1]) == ERROR || set_colors(token[2]) == ERROR)
    {
        free_array(token);
        return (ERROR);
    }

	// se ok, cria um objeto, adiciona os valores e adiciona a lista
	new_sphere = malloc(sizeof(t_sphere));
	if (!new_sphere)
	{
		free_array(token);
		return (ERROR);
	}

	fill_coordinates(token[0], new_sphere);
	new_sphere->diameter = ft_atod(token[1]);
	fill_colors(token[2], new_sphere);

	if (add_objects(data, new_sphere, SPHERE) == ERROR)
	{
		free(new_sphere);
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}
