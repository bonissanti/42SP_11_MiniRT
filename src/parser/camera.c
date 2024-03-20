/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:21 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/20 18:47:28 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	fill_coordnates(char *cam_line, t_data *data)
{
	char **split_line;

	split_line = ft_split(cam_line, ',');
	data->camera.point.x = ft_atod(split_line[0]);
	data->camera.point.y = ft_atod(split_line[1]);
	data->camera.point.z = ft_atod(split_line[2]);
	printf("x: %f, y: %f, z: %f\n", data->camera.point.x, data->camera.point.y, data->camera.point.z);
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
	data->camera.vector.x = x / magnitude;
	data->camera.vector.y = y / magnitude;
	data->camera.vector.z = z / magnitude;
	free_array(vector_str);
	return (OK);
}

t_vec3	set_up(t_data *data)
{
	t_vec3	default_up = {0, 1, 0};
	t_vec3	right;
	t_vec3	up_adjusted;
	t_vec3	forward = {
		data->camera.vector.x - data->camera.point.x,
		data->camera.vector.y - data->camera.point.y,
		data->camera.vector.z - data->camera.point.z,
	};

	forward = normalize_vector(forward);
	right = normalize_vector(cross_vector(default_up, forward));
	up_adjusted = cross_vector(forward, right);
	return(up_adjusted);
}

int	set_camera(char *fov_line, t_data *data)
{
	double	half_height;
	double	half_width;

	if (is_number(fov_line) || set_range(fov_line, 0.0, 180.0) == ERROR)
		return (print_error("Fov is not a valid number, e.g[0 to 180]"));

	data->camera.height_v = HEIGHT;
	data->camera.width_v = WIDTH;
	data->camera.fov = ft_atod(fov_line) * (M_PI / 180.0); //M_PI macro de PI da math.h 
	data->camera.aspect_ratio = (double)data->camera.width_v / (double)data->camera.height_v; // 720x480

	half_width = tan(data->camera.fov / 2.0); // metade da largura a partir da visão da camera, com /2 para simplificar
	half_height = half_width * data->camera.aspect_ratio; // se der ruim, mudar para a implementação do livro

	data->camera.half_width = half_width;
	data->camera.half_height = half_height;

	data->camera.pixel_size = (data->camera.half_width * 2 / data->camera.height_v); //se der ruim, mudar para a implementação do livro

	data->camera.up = set_up(data);
	set_camera_transform(&data->camera);
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

