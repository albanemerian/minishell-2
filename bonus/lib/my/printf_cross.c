/*
** EPITECH PROJECT, 2023
** printf_croix
** File description:
** printf_croix
*/

#include <stdarg.h>
#include <stdio.h>
#include "my.h"

int (*fr[30])(const char *format, va_list, int, int) = {
    &printf_s, &printf_d, &printf_i, &printf_c,
    &printf_o, &printf_u, &printf_x, &printf_xm, &printf_f,
    &printf_f};

static void flag_other(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == '#' && format[i + 2] == 's') {
        printf_s(format, param_infos, i, compt);
    }
    if (format[i + 1] == '#' && format[i + 2] == '%') {
        my_putchar('%');
    }
}

static void other_flags(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == '#' && format[i + 2] == 'c') {
        my_putchar((char) va_arg(param_infos, int));
    }
    if (format[i + 1] == '#' && format[i + 2] == 'u') {
        printf_u(format, param_infos, i, compt);
    } else {
        flag_other(format, param_infos, i, compt);
    }
}

static void other_flag(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == '#' && format[i + 2] == 'F') {
        printf_f(format, param_infos, i, compt);
    }
    if (format[i + 1] == '#' && format[i + 2] == 'i') {
        printf_i(format, param_infos, i, compt);
    } else {
        other_flags(format, param_infos, i, compt);
    }
}

void cross_other(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i + 1] == '#' && format[i + 2] == 'X') {
        my_putstr("0X");
        printf_xm(format, param_infos, i, compt);
    }
    if (format[i + 1] == '#' && format[i + 2] == 'f') {
        printf_f(format, param_infos, i, compt);
    } else {
        other_flag(format, param_infos, i, compt);
    }
}

void crosst(const char *format,
    va_list param_infos, int i, int compt)
{
        if (format[i + 1] == '#' && format[i + 2] == 'd') {
            printf_d(format, param_infos, i, compt);
        } else {
            cross_other(format, param_infos, i, compt);
        }
}

int printf_cross(const char *format,
    va_list param_infos, int i, int compt)
{
    while (format[i] != '\0') {
        if (format[i + 1] == '#' && format[i + 2] == 'o') {
            my_putchar('0');
            printf_o(format, param_infos, i, compt);
        }
        if (format[i + 1] == '#' && format[i + 2] == 'x') {
            my_putstr("0x");
            printf_x(format, param_infos, i, compt);
        } else {
            crosst(format, param_infos, i, compt);
        }
        return (0);
    }
    i++;
    return 0;
}
