#include "../../include/minirt.h"

int	set_brightness(char *bright_line, t_data *data)
{
	double	bright;

	if (is_number(bright_line) == ERROR)
		return (print_error("[L] Invalid bright value, e.g [0.0 ~ 1.0]"));
	bright = ft_atod(bright_line);
	if (bright < 0.0 || bright > 1.0)
		return (print_error("[L] Out of the range, e.g [0.0 ~ 1.0]"));
	data->light.brightness = bright;
	return (OK);
}

static int	fill_coordnates(char *cam_line, t_data *data)
{
	char **split_line;

	split_line = ft_split(cam_line, ',');
	data->light.position.x = ft_atod(split_line[0]);
	data->light.position.y = ft_atod(split_line[1]);
	data->light.position.z = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

int	analyze_light(char *line, t_data *data)
{
	char **token;

	token = ft_split_space(line);
	if (count_token(token, 2, "Light has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_coordnates(token[0], data);
	if (set_brightness(token[1], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}

