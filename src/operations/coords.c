/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:06 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/18 16:16:27 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_coords	set_coords(double x, double y, double z)
{
	return ((t_coords){x, y, z});
}

t_coords	add_coords(t_coords a, t_coords b)
{
	return ((t_coords){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	subtract_coords(t_coords a, t_coords b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}
