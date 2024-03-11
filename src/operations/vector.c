#include "../../include/minirt.h"

t_vec3	set_vector(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	normalize_vector(t_vec3 value)
{
	double	magnitude;
	t_vec3	normalized;

	ft_memset(&normalized, 0, sizeof(t_vec3));
	magnitude = sqrt(value.x * value.x + value.y * value.y + value.z * value.z);

	if (magnitude != 0)
	{
		normalized.x = value.x / magnitude;
		normalized.y = value.y / magnitude;
		normalized.z = value.z / magnitude;
	}
	return (normalized);
}

t_vec3	subtract_vector(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	cross_vector(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
