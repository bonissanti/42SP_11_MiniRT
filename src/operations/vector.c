#include "../../include/minirt.h"

t_vec3	normalize_vector(t_vec3 value)
{
	double	magnitude;
	t_vec3	normalized;

	magnitude = sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
	ft_memset(&normalized, 0, sizeof(t_vec3));

	if (magnitude != 0)
	{
		normalized.x = value.x / magnitude;
		normalized.y = value.y / magnitude;
		normalized.z = value.z / magnitude;
	}
	return (normalized);
}

t_vec3	substract_vector(t_vec3 a, t_vec3 b)
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