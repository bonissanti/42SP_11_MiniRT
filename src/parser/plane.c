#include "../../include/minirt.h"

int	analyze_plane(char *line, t_data *data)
{
	char	**token;

	token = ft_split_space(line);
	if (count_token(token, 3, "Plane has wrong number of arguments"))
		return (ERROR);
	if (set_coordinate(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	if (set_vector_3d(token[1], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	if (set_colors(token[2]) = ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}
