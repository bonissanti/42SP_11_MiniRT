#include "../include/minirt.h"

int analyze_amblight(char *line)
{
    int     argc;
    int     i;
    char    **token;

    i = -1;
    argc = 0;
    token = ft_split(line, ' ');
    while (token[++i])
    {
        argc++;
        printf("%s\n", token[i]);
    }
    printf("argc: %d\n", argc);
    free_array(token);
    return (0);    

}