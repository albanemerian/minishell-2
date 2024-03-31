/*
** EPITECH PROJECT, 2023
** printf_x
** File description:
** printf_x
*/

#include <stdarg.h>
#include "my.h"

void printf_xx(const char *format, va_list param_infos, int q, char *hex)
{
    for (int j = q - 1; j >= 0; j--) {
        my_putchar(hex[j]);
    }
}

int printf_x(const char *format, va_list param_infos, int i, int compt)
{
    char hex[500];
    long int q = 0;
    long int k;
    long int temp = 0;

    k = va_arg(param_infos, int);
    while (k != 0) {
        temp = k % 16;
        if (temp < 10) {
            hex[q] = temp + 48;
            q++;
        } else {
            hex[q] = temp + 87;
            q++;
        }
        k = k / 16;
    }
    printf_xx(format, param_infos, q, hex);
    return (0);
}
