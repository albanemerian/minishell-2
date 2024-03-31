/*
** EPITECH PROJECT, 2023
** printf_u
** File description:
** printf_u
*/
#include "my.h"
#include <stdarg.h>

int printf_u(const char *format,
    va_list param_infos, int i, int compt)
{
    unsigned int j = va_arg(param_infos, unsigned int);

    if (j >= 0) {
        my_unsigned_nbr(j);
    }
    return (nb_length(j));
}
