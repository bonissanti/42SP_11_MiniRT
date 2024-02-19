#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../my_libft/include/libft.h"

typedef enum e_bool 
{
    false,
    true
}           t_bool;

typedef struct s_parser
{
    int    has_A;
    int    has_C;
    int    has_L;
}               t_parser;

typedef struct s_ambilight
{
    double  ratio;
    char    *color;
}               t_ambilight;

typedef struct s_data
{
	char	buffer[4096];

} t_data;

// #############################  Validation  #################################

int	    valid_file(char *file, t_data *data);

// #############################  Parser  #####################################

int	    parse_lines(t_data *data);
int     analyze_amblight(char *line);
// int	    count_identifiers(char *line, t_parser *parser);

// #############################  Aux Functions  ##############################

size_t	ft_strxspn(const char *str, const char *set, int mode);
char	*ft_strtok(char *str, const char *delim);
void    free_array(char **array);

#endif