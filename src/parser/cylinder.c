#include "../../include/minirt.h"

static int	fill_coordinates(char *line, t_data *data)
{
	char **split;

	split = ft_split(line, ',');
	data->cylinder.position.x = ft_atod(split[0]);
	data->cylinder.position.y = ft_atod(split[1]);
	data->cylinder.position.z = ft_atod(split[2]);
	free_array(split);	
	return (OK);
}

static int	fill_colors(char *line, t_data *data)
{
	char **split_line;

	split_line = ft_split(line, ',');
	data->cylinder.color[0] = ft_atod(split_line[0]);
	data->cylinder.color[1] = ft_atod(split_line[1]);
	data->cylinder.color[2] = ft_atod(split_line[2]);
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
	data->cylinder.vec_point.x = x / magnitude;
	data->cylinder.vec_point.y = y / magnitude;
	data->cylinder.vec_point.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}

int	analyze_cylinder(char *line, t_data *data)
{
	char	**token;

	token = ft_split_space(line);
	if (count_token(token, 5, "Cylinder has wrong number of arguments"))
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
	data->cylinder.diameter = ft_atod(token[2]);
	data->cylinder.height = ft_atod(token[3]);
	if (set_colors(token[4]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_colors(token[4], data);
	free_array(token);
	return (ERROR);
}
