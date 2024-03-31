/*
** EPITECH PROJECT, 2023
** printf_l
** File description:
** printf_l
*/

#include "my.h"
#include <stdarg.h>
#include <unistd.h>

static void flag_medium(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == 'l' && format[i + 2] == '%') {
        my_putchar('%');
    }
}

static void flag_base(const char *format,
    va_list param_infos, int i, int compt)
{
        flag_medium(format, param_infos, i, compt);
}

static void flag_simple(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == 'l' && format[i + 2] == 'f') {
        printf_f(format, param_infos, i, compt);
    }
    if (format[i + 1] == 'l' && format[i + 2] == 'F') {
        printf_fm(format, param_infos, i, compt);
    } else {
        flag_base(format, param_infos, i, compt);
    }
}

static void other_flagsi(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == 'l' && format[i + 2] == 'c') {
        printf_c(format, param_infos, i, compt);
    }
    if (format[i + 1] == 'l' && format[i + 2] == 's') {
        printf_s(format, param_infos, i, compt);
    } else {
        flag_simple(format, param_infos, i, compt);
    }
}

static void other_flag(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == 'l' && format[i + 2] == 'X') {
        printf_xm(format, param_infos, i, compt);
    }
    if (format[i + 1] == 'l' && format[i + 2] == 'u') {
        printf_u(format, param_infos, i, compt);
    } else {
    other_flagsi(format, param_infos, i, compt);
    }
}

void other_flags(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == 'l' && format[i + 2] == 'o') {
        printf_o(format, param_infos, i, compt);
    }
    if (format[i + 1] == 'l' && format[i + 2] == 'x') {
        printf_x(format, param_infos, i, compt);
    } else {
        other_flag(format, param_infos, i, compt);
    }
}

int printf_l(const char *format,
    va_list param_infos, int i, int compt)
{
    long int num = va_arg(param_infos, long int);
    long int nb = va_arg(param_infos, long int);

    if (format[i + 1] == 'l' && format[i + 2] == 'd') {
        my_put_nbr(num);
    }
    if (format[i + 1] == 'l' && format[i + 2] == 'i') {
        my_put_nbr(nb);
    } else {
        other_flags(format, param_infos, i, compt);
    }
    return 0;
}
