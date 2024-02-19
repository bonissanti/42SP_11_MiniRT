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