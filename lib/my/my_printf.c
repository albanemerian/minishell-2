/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** my_printf
*/

#include "my.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int (*ft[30])(const char *format, va_list, int, int) = {
    &printf_s, &printf_d, &printf_i, &printf_c,
    &printf_o, &printf_u, &printf_x, &printf_xm, &printf_f,
    &printf_fm, &printf_cross,
    &printf_l};

int (*fp[5])(const char *format, va_list, int, int) = {
    &printf_cross};

void flag_modifier(const char *format, va_list param_infos, int i, int compt)
{
    char flag_h[8] = {'s', 'd', 'i', 'c', 'o', 'x', 'X', 'l'};

    for (int index = 0; index <= 8; index++) {
        if (format[i + 1] == flag_h[index]) {
            ft[index](format, param_infos, i, compt);
            break;
        }
    }
}

int flag_test(const char *format,
    va_list param_infos, int i, int compt)
{
    char flag_t[30] = {'s', 'd', 'i', 'c',
        'o', 'u', 'x', 'X', 'f', 'F', 'l'};

    if (format[i + 1] == '%') {
        my_putchar('%');
        return (1);
    }
    for (int index = 0; index <= 15; index++) {
        if (format[i + 1] == flag_t[index]) {
            ft[index](format, param_infos, i, compt);
            break;
        }
    }
    return 0;
}

int flag_precision(const char *format,
    va_list param_infos, int i, int compt)
{
    char flag_t[5] = {'o', 'x', 'X', '#'};

    for (int index = 0; index <= 4; index++) {
        if (format[i] == flag_t[index]) {
            fp[index](format, param_infos, i, compt);
            return (0);
        }
    }
    flag_modifier(format, param_infos, i, compt);
    return 1;
}

int my_multiple(const char *format,
    va_list param_infos, int i, int compt)
{
    if (format[i] == '%' && format[i + 1] == '#') {
        flag_precision(format, param_infos, i, compt);
        printf_cross(format, param_infos, i, compt);
        i++;
        i++;
    } else {
        flag_test(format, param_infos, i, compt);
        i++;
    }
    if (format[i] == 'l') {
        flag_modifier(format, param_infos, i, compt);
        printf_l(format, param_infos, i, compt);
        i++;
    }
    return (i);
}

void print(const char *format, ...)
{
    va_list param_infos;
    int compt = 0;
    int i = 0;

    va_start(param_infos, format);
    while (format[i] != '\0') {
        if (format[i] != '%') {
            my_putchar(format[i]);
            compt++;
        } else {
            i = my_multiple(format, param_infos, i, compt);
        }
        i++;
    }
}
