/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:10 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/15 17:10:22 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "../MLX42/include/MLX42/MLX42.h"

/* config window */

# define HEIGHT 200
# define WIDTH 200
# define TITLE "miniRTARDOS"

/* structs to mlx */

typedef struct s_img
{
	int			bpp;
	int			line_size;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	mlx_t		*win_ptr;
	mlx_image_t	*img_ptr;
	int			width;
	int			*pixels;
	int			height;
	t_img		img;
}				t_mlx;

void			create_mlx_window(t_mlx *mlx);

#endif
