#include "../../include/minirt.h"

void	init_structs(t_data *data)
{
	ft_memset(data, 0, sizeof(data));
	ft_memset(&data->parser, 0, sizeof(data->parser));
	ft_memset(&data->amblight, 0, sizeof(data->amblight));
}
