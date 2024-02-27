#include "../../include/minirt.h"

// static int	fill_coordinates(char *line, t_data *data)
// {
// 	char **split;
//
// 	split = ft_split(line, ',');
// 	//	sphere struct;
// 	//	free
// 	return (OK);
// }
//


int	analyze_sphere(char *line, t_data *data)
{
	char **token;

	(void)data;
	token = ft_split_space(line);
	if (count_token(token, 2, "[sp] Sphere has wrong number of arguments"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	if (is_number(token[1]) == ERROR)
	{
		free_array(token);
		return (print_error("[sp] Range is not a value"));
	}
	// if (set_colors(token[2]) == ERROR)
	// {
	// 	free_array(token);
	// 	return (ERROR);
	// }

	// fill_coordinates(token[0], data);
	free_array(token);
	return (OK);
}
