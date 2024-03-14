#ifndef RAY_H
# define RAY_H

# include "structs.h"

t_ray	ray_for_pixel(t_camera *camera, int x, int y);
bool	hit_sphere(const t_sphere *sphere, const t_ray *ray, double *closest_t);
t_color	trace_ray(t_data *data, t_ray ray);

#endif
