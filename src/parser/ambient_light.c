#include "../../include/minirt.h"

static int set_ambient_ratio(char *ratio_line, t_data *data)
{
	double	ratio;

	ratio =	ft_atod(ratio_line);
	if (ratio < 0.0 || ratio > 1.0)
	{
		ft_putstr_fd("Error\nInvalid ratio value or out of the range [0.0 - 1.0]\n", 2);
		return (ERROR);
	}
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
		{
			ft_putstr_fd("Error:\nColor out of range [0, 255]\n", 2);
			return (ERROR);
		}
		data->amblight.color[i] = color;
	}
	return (OK);
}

static int	set_ambient_colors(char *color_line, t_data *data)
{
	int		i;
	int		argc;
	char 	**token;

	i = -1;
	argc = 0;
	token = ft_split(color_line, ',');
	while (token[++i])
		argc++;
	if (argc != 3)
	{
		ft_putstr_fd("Error:\nIncorrect number of RGB componentes, [e.g 255,255,255]\n", 2);
		free_array(token);
		return (ERROR);
	}
	if (validate_colors(token, data) != 0)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token); 
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
