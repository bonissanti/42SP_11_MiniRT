#include "../../include/minirt.h"

static int	fill_coordnates(char *cam_line, t_data *data)
{
	char **split_line;

	split_line = ft_split(cam_line, ',');
	data->camera.point.x = ft_atod(split_line[0]);
	data->camera.point.y = ft_atod(split_line[1]);
	data->camera.point.z = ft_atod(split_line[2]);
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
	data->camera.vector.x = x / magnitude;
	data->camera.vector.y = y / magnitude;
	data->camera.vector.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}


int	set_fov(char *fov_line, t_data *data)
{
	if (is_number(fov_line))
		return (print_error("Fov is not a valid number, e.g[0 to 180]"));
	else if (set_range(fov_line, 0.0, 180.0))
		return (print_error("[C] Invalid FOV"));
	data->camera.fov = ft_atod(fov_line);
	return (OK);
}


int	analyze_camera(char *line, t_data *data)
{
	char **token;

	token = ft_split_space(line);
	if (count_token(token, 3, "Camera has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_coordnates(token[0], data);
	if (set_vector_3d(token[1]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_vector(token[1], data);
	if (set_fov(token[2], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}

