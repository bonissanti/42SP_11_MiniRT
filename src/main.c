#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	t_data data;

	memset(&data, 0, sizeof(t_data)); // add libft
	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	else if (valid_file(argv[1], &data) != 0)
		return (1);
	else if (!parse_lines(&data))
		return (1);
	return (0);
}