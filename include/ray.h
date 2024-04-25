/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:38:26 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 13:39:52 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structs.h"

t_ray		ray_for_pixel(t_camera *camera, double x, double y);
bool		hit_sphere(const t_sphere *sphere, t_ray ray, double *t);
bool		hit_plane(t_ray ray, double t[2]);
t_color		trace_ray(t_data *data, t_ray ray);
t_ray		ray_transform(t_ray ray, t_matrix matrix);
t_vec3		get_intersection_point(t_ray ray, double t);
t_coords	ray_position(t_ray ray, double distance);

// # hit cylinder
bool		hit_cylinder(const t_cylinder *cyl, t_ray ray, double t[2]);
t_bhaskara	cylinder_bhask(const t_ray ray);
bool		set_t(t_bhaskara result, double t[2]);

#endif
