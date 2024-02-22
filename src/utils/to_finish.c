#include "../include/minirt.h"

void    free_array(char **array)
{
    char **ptr;

    ptr = array;
    while (*ptr)
    {
        free(*ptr);
        ptr++;
    }
    free(array);
}

int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return (ERROR);
}
