#include "../../include/minirt.h"

void	init_structs(t_data *data)
{
	ft_memset(data, 0, sizeof(data));
	ft_memset(&data->parser, 0, sizeof(data->parser));
	ft_memset(&data->amblight, 0, sizeof(data->amblight));
	ft_memset(&data->camera, 0, sizeof(data->camera));
	ft_memset(&data->camera.point, 0, sizeof(data->camera.point));
	ft_memset(&data->light, 0, sizeof(data->light));
	ft_memset(&data->sphere, 0, sizeof(data->sphere));
	ft_memset(&data->plane, 0, sizeof(data->plane));
	ft_memset(&data->cylinder, 0, sizeof(data->cylinder));

}

