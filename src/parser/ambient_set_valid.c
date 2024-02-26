#include "../../include/minirt.h"

static int	validate_colors(char **color_str, t_data *data)
{
	int	i;
	int	color;

	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(color_str[i]);
		if (color < 0 || color > 255)
			return (print_error("[A] Color out of range [0, 255]"));
		data->amblight.color[i] = color;
	}
	return (OK);
}

int	set_ambient_ratio(char *ratio_line, t_data *data)
{
	double	ratio;

	if (is_number(ratio_line) == ERROR)
		return (print_error("[A] Invalid ratio value"));
	ratio =	ft_atod(ratio_line);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_error("[A] Ratio out of the range [0.0 - 1.0]"));
	data->amblight.ratio = ratio;
	return (OK);
}

int	set_ambient_colors(char *color_line, t_data *data)
{
	char 	**color_split;

	color_split = ft_split(color_line, ',');
	if (count_token(color_split, 3, "[A] Incorrect number of RGB componentes\n"))
		return (ERROR);
	if (validate_colors(color_split, data) != 0)
	{
		free_array(color_split);
		return (ERROR);
	}
	free_array(color_split); 
	return (OK);
}

