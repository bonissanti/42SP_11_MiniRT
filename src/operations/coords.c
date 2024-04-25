/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:06 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:30:59 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_coords	set_coords(double x, double y, double z)
{
	return ((t_coords){x, y, z});
}

t_vec3	set_coords_to_vector(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	subtract_coords(t_coords a, t_coords b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_coords	add_coords(t_coords a, t_coords b)
{
	t_coords	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
