#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_data *data)
{
	char **split_line;

	split_line = ft_split(line, ',');
	data->objects.plane.position.x = ft_atod(split_line[0]);
	data->objects.plane.position.y = ft_atod(split_line[1]);
	data->objects.plane.position.z = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

static int	fill_vector(char *line, t_data *data)
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
	data->objects.plane.vector.x = x / magnitude;
	data->objects.plane.vector.y = y / magnitude;
	data->objects.plane.vector.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}

static int	fill_colors(char *line, t_data *data)
{
	char **split_line;

	split_line = ft_split(line, ',');
	data->objects.plane.color[0] = ft_atod(split_line[0]);
	data->objects.plane.color[1] = ft_atod(split_line[1]);
	data->objects.plane.color[2] = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

int	analyze_plane(char *line, t_data *data)
{
	char	**token;

	token = ft_split_space(line);
	if (count_token(token, 3, "Plane has wrong number of arguments"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_coordinates(token[0], data);
	if (set_vector_3d(token[1]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_vector(token[1], data);
	if (set_colors(token[2]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_colors(token[2], data);
	free_array(token);
	return (OK);
}

