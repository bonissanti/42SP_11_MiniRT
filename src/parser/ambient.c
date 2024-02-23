#include "../../include/minirt.h"

int analyze_amblight(char *line, t_data *data)
{
	char    **token;

    token = ft_split_space(line);
	if (count_token(token, 2, "Error\nAmbient light has wrong number of arguments\n"))
		return (ERROR);
    if (set_ambient_ratio(token[0], data) != 0)
	{
		free_array(token);
		return (ERROR);
	}
	if (set_ambient_colors(token[1], data) != 0)
	{
		free_array(token);
		return (ERROR);
	}
    free_array(token);
    return (OK);
}

