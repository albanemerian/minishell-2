/*
** EPITECH PROJECT, 2023
** printf_i
** File description:
** i
*/

#include <stdarg.h>
#include "my.h"

int printf_i(const char *format,
    va_list param_infos, int i, int compt)
{
    int k;

    k = (int) va_arg(param_infos, int);
    my_put_nbr(k);
    return (nb_length(k));
}
