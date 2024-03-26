#include "../../include/minirt.h"

bool	check_equal_doubles(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}
