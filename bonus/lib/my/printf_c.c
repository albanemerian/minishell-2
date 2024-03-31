/*
** EPITECH PROJECT, 2023
** printf_c
** File description:
** printf_c
*/

#include <stdarg.h>
#include "my.h"

int printf_c(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == 'c') {
        my_putchar((char) va_arg(param_infos, int));
    }
    return (1);
}
