#include "../../include/minirt.h"

int	set_coordinates(char *coord_line, t_data *data)
{
	char **coord_split;
	
	coord_split = ft_split(coord_line, ',');
	if (count_token(coord_split, 3, "Incorrect number of coordinates, e.g [-10.0,0,0]\n"))
		return (ERROR);
	if (validate_split(coord_split) == ERROR)
	{
		free_array(coord_split);
		return (ERROR); 
	}
	data->camera.point.x = ft_atod(coord_split[0]);
	data->camera.point.y = ft_atod(coord_split[1]);
	data->camera.point.z = ft_atod(coord_split[2]);
	free_array(coord_split);
	return (OK); 
}

int	set_vector_3d(char *vector_line, t_data *data)
{
	char **vector_split;

	vector_split = ft_split(vector_line, ',');
	if (count_token(vector_split, 3, "Incorrect number of vector, e.g[0,0,1]"))
		return (ERROR);
	if (validate_split(vector_split) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	if (validate_range_3d(vector_split) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	if (normalize_and_set(vector_split, data) == ERROR)
	{
		free_array(vector_split);
		return (ERROR);
	}
	free_array(vector_split);
	return (OK);
}

int	set_fov(char *fov_line, t_data *data)
{
	if (is_number(fov_line))
		return (print_error("Fov is not a valid number, e.g[0 to 180]"));
	else if (validate_fov(fov_line, data) == ERROR)
		return (ERROR);
	return (OK);
}
