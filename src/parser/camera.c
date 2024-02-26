#include "../../include/minirt.h"

int	is_number(char *coord)
{
	int	i;
	int	count_dot;

	i = -1;
	count_dot = 0;
	if (coord[0] == '-')
		i++;
	while (coord[++i] != '\0')
	{
		if (coord[i] == '.')
		{
			count_dot++;
			if (count_dot > 1)
				return (ERROR);
		}
		else if (!ft_isdigit(coord[i]))
			return (ERROR);
	}
	return (OK);	
}

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
	if (set_vector_3d(token[1], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	else if (set_fov(token[2], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}

