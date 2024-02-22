#include "../../include/minirt.h"

static int set_ambient_ratio(char *ratio_line, t_data *data)
{
	double	ratio;

	ratio =	ft_atod(ratio_line);
	if (ratio < 0.0 || ratio > 1.0)
		return (print_error("Invalid ratio value or out of the range [0.0 - 1.0]\n"));
	data->amblight.ratio = ratio;
	return (OK);
}

static int	validate_colors(char **color_str, t_data *data)
{
	int	i;
	int	color;

	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(color_str[i]);
		if (color < 0 || color > 255)
			return (print_error("Color out of range [0, 255]\n"));
		data->amblight.color[i] = color;
	}
	return (OK);
}

static int	set_ambient_colors(char *color_line, t_data *data)
{
	int		i;
	int		argc;
	char 	**color_split;

	i = -1;
	argc = 0;
	color_split = ft_split(color_line, ',');
	if (count_token(color_split, 3, "Incorrect number of RGB componentes\n"))
		return (ERROR);
	// while (color_split[++i])
	// 	argc++;
	// if (argc != 3)
	// {
	// 	free_array(color_split);
	// 	return (print_error("Incorrect number of RGB componentes, [e.g 255,255,255]\n"));
	// }
	if (validate_colors(color_split, data) != 0)
	{
		free_array(color_split);
		return (ERROR);
	}
	free_array(color_split); 
	return (OK);
}

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
