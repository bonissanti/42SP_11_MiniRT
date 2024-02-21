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

static int	validate_coordinates(char **coord_str, t_data *data)
{
	int	i;
	int	count_dot;

	i = -1;
	(void)data;
	count_dot = 0;
	while (++i < 3)
	{
		if (is_number(coord_str[i]) == ERROR)
		{
			printf("deu ruim\n");
			return (ERROR);
		}
	}
	return (OK);
}

static int	set_coordinates(char **coord_line, t_data *data)
{
	int	i;
	int	argc;
	
	i = -1;
	argc = 0;
	while (coord_line[++i]) 
		argc++; 
	if (argc != 3) 
	{ 
		ft_putstr_fd("Error\nIncorrect number of coordinates, e.g [-10.0,0,0]\n", 2); 
		free_array(coord_line);
		return (1); 
	}
	if (validate_coordinates(coord_line, data) != 0) 
	{ 
		free_array(coord_line);
		return (ERROR); 
	} 
	free_array(coord_line);
	return (OK); 
}

int	analyze_camera(char *line, t_data *data)
{
	char **token;

	token = ft_split_space(line);
	if (count_token(token, 2, "Error\nCamera has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token + 1, data) != 0)
	{
		free_array(token);
		return (ERROR);
	}
	// if (set_normalized_3d(token[1], data) != 0)
	// { free_array(token);
	// 	return (1);
	// }
	// if (set_fov(token[1], data) != 0)
	// {
	// 	free_array(token);
	// 	return (1);
	// }
	free_array(token);
	return (OK);
}
