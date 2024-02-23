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

int	analyze_camera(char *line, t_data *data)
{
	char **token;

	token = ft_split_space(line);
	if (count_token(token, 3, "Camera has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	else if (set_vector_3d(token[1], data) == ERROR)
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

