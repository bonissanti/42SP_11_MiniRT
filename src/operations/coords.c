#include "../../include/minirt.h"

t_coords	set_coords(double x, double y, double z)
{
	return ((t_coords){x, y, z});
}

t_vec3	subtract_coords(t_coords a, t_coords b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}
