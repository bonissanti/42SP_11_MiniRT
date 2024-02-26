// #include "../../include/minirt.h"
//
// static int	fill_coordinates(char *line, t_data *data)
// {
// 	char **split;
//
// 	split = ft_split(line, ',');
// 	//	sphere struct;
// 	//	free
// 	return (OK);
// }
//

int	analyze_sphere(char *line, t_data *data)
{
	char **sp_split;

	sp_split = ft_split_space(line);
	if (count_token(token, 3, "[sp] Sphere has wrong number of arguments"))
		return (ERROR);
	if (set_coordinates(token[0], data) == ERROR)
	{
		free_array(sp_split);
		return (ERROR);
	}
	fill_coordinates(token[0], data);
	free_array(sp_split);
	return (OK);
}
