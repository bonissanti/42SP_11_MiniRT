#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../my_libft/include/libft.h"

typedef struct s_parser
{
    int    has_A;
    int    has_C;
    int    has_L;
}               t_parser;

typedef struct s_amblight
{
	double  ratio;
   	int    color[3];
}               t_amblight;

typedef struct s_data
{
	char		buffer[4096];
	t_parser	parser;
	t_amblight	amblight;
} 				t_data;

// ################################# Init #####################################

void	init_structs(t_data *data);

// #############################  Validation  #################################

int	    valid_file(char *file, t_data *data);

// #############################  Parser  #####################################

int	    parse_lines(t_data *data);
int     analyze_amblight(char *line, t_data *data);

// #############################  Aux Functions  ##############################

size_t	ft_strxspn(const char *str, const char *set, int mode);
char	*ft_strtok(char *str, const char *delim);
void    free_array(char **array);
int		count_token(char **tokens, int expected_count, const char *msg);
double	ft_atod(char *str);

#endif
