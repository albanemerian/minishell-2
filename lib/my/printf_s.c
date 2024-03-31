/*
** EPITECH PROJECT, 2023
** printf_s
** File description:
** s
*/

#include <stdarg.h>
#include "my.h"

int printf_s(const char *format,
    va_list param_infos, int i, int compt)
{
    char *cc;

    cc = (char *) va_arg(param_infos, char *);
    my_putstr(cc);
    return (my_strlen(cc));
}
