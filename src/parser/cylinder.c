#include "../../include/minirt.h"

int	analyze_cylinder(char *line, t_data *data)
{
	char	**token;

	token = ft_split_space(line);
	if (count_token(token, 4, "Cylinder has wrong number of arguments"))
		return (ERROR);
	if (set_coordinates(token[0]))
}
