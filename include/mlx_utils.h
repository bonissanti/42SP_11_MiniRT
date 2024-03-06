#ifndef MLX_UTILS_H 
# define MLX_UTILS_H

# include "../MLX42/include/MLX42/MLX42.h"

/* config window */

# define HEIGHT 480
# define WIDTH 720
# define TITLE "miniRTARDOS"

/* structs to mlx */

typedef struct s_img
{
	int			bpp;
	int			line_size;
	int			endian;
}				t_img;

typedef struct s_canvas
{
	mlx_t		*win_ptr;
	mlx_image_t	*img_ptr;
	int			width;
	int			height;
	t_img		img;
}				t_canvas;

/* void	run_render(t_canvas *mlx); */

#endif
