/*
** EPITECH PROJECT, 2023
** printf_d
** File description:
** printf_d
*/

#include <stdarg.h>
#include "my.h"

int nb_length(int n)
{
    int len = 1;

    while (n > 9) {
        n = n / 10;
        len ++;
    }
    return (len);
}

int printf_d(const char *format,
    va_list param_infos, int i, int compt)
{
    int k;

    k = (int) va_arg(param_infos, int);
    my_put_nbr(k);
    return (nb_length(k));
}
