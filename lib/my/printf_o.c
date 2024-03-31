/*
** EPITECH PROJECT, 2023
** printf_o
** File description:
** printf_o
*/

#include <stdarg.h>
#include "my.h"

int printf_o(const char *format,
    va_list param_infos, int i, int compt)
{
    int o[100];
    int p = 0;
    int j;
    int k;

    k = (int) va_arg(param_infos, int);
    while (k != 0) {
        o[p] = k % 8;
        k = k / 8;
        p++;
    }
    for (j = p - 1; j >= 0; j--) {
        my_put_nbr(o[j]);
    }
    return (nb_length(o[j]));
}
