#include "../../include/minirt.h"

int validate_range_3d(char **str)
{
	int	i;
	int	range;

	i = -1;
	while (++i < 3)
	{
		range = ft_atod(str[i]);
		if (range < -1.0 || range > 1.0)
			return (print_error("Value out of range, e.g[-1.1,0.0,1.0]"));
	}
	return (OK);
}

int	validate_split(char **str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (is_number(str[i]) == ERROR)
			return (print_error("This is not a valid coordinate\n"));
	}
	return (OK);
}

int	normalize_and_set(char **vector_str, t_data *data)
{
	double	x;
	double	y;
	double	z;
	double	magnitude;

	x = ft_atod(vector_str[0]);
	y = ft_atod(vector_str[1]);
	z = ft_atod(vector_str[2]);
	magnitude = sqrt(x * x + y * y + z * z);

	if (fabs(magnitude) < EPSILON)
		return (print_error("Cannot normalize a zero vector"));
	data->camera.vec_point.x = x / magnitude;
	data->camera.vec_point.y = y / magnitude;
	data->camera.vec_point.z = z / magnitude;
	return (OK);
}

int	validate_fov(char *fov_line, t_data *data)
{
	int	fov;

	fov = ft_atod(fov_line);
	if (fov < 0.0 || fov > 180.0)
		return (print_error("Fov outside of the degrees in range, e.g[0 to 180]"));
	data->camera.fov = fov;
	printf("fov: %f\n", data->camera.fov);
	return (OK);
}
