#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_data *data)
{
	char **split;

	split = ft_split(line, ',');
	data->objects.sphere.position.x = ft_atod(split[0]);
	data->objects.sphere.position.y = ft_atod(split[1]);
	data->objects.sphere.position.z = ft_atod(split[2]);
	free_array(split);
	return (OK);
}

static int	fill_colors(char *line, t_data *data)
{
	char **split_line;

	split_line = ft_split(line, ',');
	data->objects.sphere.color[0] = ft_atod(split_line[0]);
	data->objects.sphere.color[1] = ft_atod(split_line[1]);
	data->objects.sphere.color[2] = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

int	analyze_sphere(char *line, t_data *data)
{
	char **token;

	(void)data;
	token = ft_split_space(line);
	if (count_token(token, 3, "[sp] Sphere has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_coordinates(token[0], data);
	if (is_number(token[1]) == ERROR)
	{
		free_array(token);
		return (print_error("[sp] Range is not a value"));
	}
	data->objects.sphere.diameter = ft_atod(token[1]);
	if (set_colors(token[2]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_colors(token[2], data);
	free_array(token);
	return (OK);
}
