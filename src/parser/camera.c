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

static int	validate_split(char **str, t_data *data)
{
	int	i;
	int	count_dot;

	i = -1;
	count_dot = 0;
	while (++i < 3)
	{
		if (is_number(str[i]) == ERROR)
			return (print_error("This is not a valid coordinate\n"));
	}
	data->camera->point->x = ft_atod(str[0]);
	data->camera->point->y = ft_atod(str[1]);
	data->camera->point->z = ft_atod(str[2]);
	return (OK);
}

static int	set_coordinates(char *coord_line, t_data *data)
{
	int	i;
	int	argc;
	char **coord_split;
	
	i = -1;
	argc = 0;
	coord_split = ft_split(coord_line, ',');
	if (count_token(coord_split, 3, "Incorrect number of coordinates, e.g [-10.0,0,0]\n"))
		return (ERROR);
	if (validate_split(coord_split, data) == ERROR)
	{
		free_array(coord_split);
		return (ERROR); 
	}
	free_array(coord_split);
	return (OK); 
}

static	int set_normalized_3d(char *vector_line, t_data *data)
{
	int i;
	int argc;
	char **vector_line;

	i = -1;
	argc = 0;
	vector_split = ft_split(vector_line, ',');
	if (count_token(vector_split, 3, "Incorrect number of vector, e.g[0,0,0]"))
		return (ERROR);
	if (validate_split(vector_split, data) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	free_array(vector_split);
	return (OK);
}

int	analyze_camera(char *line, t_data *data)
{
	char **token;

	token = ft_split_space(line);
	if (count_token(token, 3, "Camera has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0], data) != 0)
	{
		free_array(token);
		return (ERROR);
	}
	if (set_normalized_3d(token[1], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}
