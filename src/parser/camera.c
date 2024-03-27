/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:21 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/18 12:19:08 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordnates(char *cam_line, t_data *data)
{
	char **split_line;

	split_line = ft_split(cam_line, ',');
	data->camera.origin.x = ft_atod(split_line[0]);
	data->camera.origin.y = ft_atod(split_line[1]);
	data->camera.origin.z = ft_atod(split_line[2]);
	free_array(split_line);
	return (OK);
}

static int	fill_vector(char *line, t_data *data)
{
	double	x;
	double	y;
	double	z;
	double	magnitude;
	char	**vector_str;

	vector_str = ft_split(line, ',');
	x = ft_atod(vector_str[0]);
	y = ft_atod(vector_str[1]);
	z = ft_atod(vector_str[2]);
	magnitude = sqrt(x * x + y * y + z * z);
	data->camera.orientation.x = x / magnitude;
	data->camera.orientation.y = y / magnitude;
	data->camera.orientation.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}

t_vec3	set_up(t_vec3 orientation)
{
	t_vec3	correct_up;
	double	result;

	correct_up = set_vector(0, 1, 0);
	result = dot_product(orientation, set_vector(0, 1, 0));
	if (check_equal_doubles(result, 1))
		correct_up = set_vector(0, 0, 1);
	else if (check_equal_doubles(result, -1))
		correct_up = set_vector(0, 0, -1);
	return (normalize_vector(correct_up));
}
		

int	set_camera(char *fov_line, t_data *data)
{
	if (is_number(fov_line) || set_range(fov_line, 0.0, 180.0) == ERROR)
		return (print_error("Fov is not a valid number, e.g[0 to 180]"));

	data->camera.height_v = HEIGHT;
	data->camera.width_v = WIDTH;
	data->camera.fov = ft_atod(fov_line) * (M_PI / 180.0);
	data->camera.half_width = tan(data->camera.fov / 2.0);
	data->camera.half_height = data->camera.half_width * (double)WIDTH / (double)HEIGHT;
	data->camera.pixel_size = (data->camera.half_width * 2) / (double)HEIGHT;
	set_camera_transform(data->camera, data->camera.origin, data->camera.orientation, set_up(data->camera.orientation));
	return (OK);
}

int	analyze_camera(char *line, t_data *data)
{
	char **token;

	token = ft_split_space(line);
	if (count_token(token, 3, "Camera has wrong number of arguments\n"))
		return (ERROR);
	if (set_coordinates(token[0]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_coordnates(token[0], data);
	if (set_vector_3d(token[1]) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	fill_vector(token[1], data);
	if (set_camera(token[2], data) == ERROR)
	{
		free_array(token);
		return (ERROR);
	}
	free_array(token);
	return (OK);
}

