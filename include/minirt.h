#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/include/libft.h"
# include "elements.h"
# include "structs.h"

# define OK 		0 
# define ERROR 		1
# define EPSILON	0.00001

// # Init --------------------

void	init_structs(t_data *data);
int	    valid_file(char *file, t_data *data);
int	    parse_lines(t_data *data);

// # Aux ---------------------

int		count_token(char **tokens, int expected_count, const char *msg);
int		print_error(char *msg);
int		is_number(char *coord);
char	*ft_strtok(char *str, const char *delim);
void	free_array(char **array);
double	ft_atod(char *str);
size_t	ft_strxspn(const char *str, const char *set, int mode);

#endif
