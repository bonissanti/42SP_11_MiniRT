#include "../../include/minirt.h"

static int set_ambient_ratio(char *ratio_line, t_data *data)
{
	double	ratio;

	ratio =	ft_atod(ratio_line);
	if (ratio < 0.0 || ratio > 1.0)
	{
		ft_putstr_fd("Error\nInvalid ratio value or out of the range [0.0 - 1.0]\n", 2);
		return (1);
	}
	data->amblight.ratio = ratio;
	printf("ratio = %f\n", data->amblight.ratio);
	return (0);
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
			return (1);
		}
		data->amblight.color[i] = color;
	}
	printf("color[0] = %d\n", data->amblight.color[0]);
	printf("color[1] = %d\n", data->amblight.color[1]);
	printf("color[2] = %d\n", data->amblight.color[2]);
	return (0);
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
		return (1);
	}
	if (validate_colors(token, data) != 0)
	{
		free_array(token);
		return (1);
	}
	free_array(token);
	return (0);
}

int analyze_amblight(char *line, t_data *data)
{
	char    **token;

    token = ft_split(line, ' ');
	if (count_token(token, 2, "Error\nAmbient light has wrong number of arguments\n"))
		return (1);
    if (set_ambient_ratio(token[0], data) != 0)
	{
		free_array(token);
		return (1);
	}
	if (set_ambient_colors(token[1], data) != 0)
	{
		free_array(token);
		return (1);
	}
    free_array(token);
    return (0);    
}
