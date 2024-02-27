#include "../../include/minirt.h"

static int	fill_colors(char *line, t_data *data)
{
	char **split_line;

	split_line = ft_split(line, ',');
	data->amblight.color[0] = ft_atod(split_line[0]);
	data->amblight.color[1] = ft_atod(split_line[1]);
	data->amblight.color[2] = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

int analyze_amblight(char *line, t_data *data)
{
	char    **token;

    token = ft_split_space(line);
	if (count_token(token, 2, "Ambient light has wrong number of arguments\n"))
		return (ERROR);
    if (set_range(token[0], 0.0, 1.0) == ERROR)
	{
		free_array(token);
		return (print_error("[A] Invalid ratio"));
	}
	data->amblight.ratio = ft_atod(token[0]);
	if (set_colors(token[1]) != 0)
	{
		free_array(token);
		return (ERROR);
	}
	fill_colors(token[1], data);
    free_array(token);
    return (OK);
}

