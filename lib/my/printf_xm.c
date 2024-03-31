/*
** EPITECH PROJECT, 2023
** printf_xm
** File description:
** printf_xm
*/

#include <stdarg.h>
#include "my.h"

void printf_xxm(const char *format, va_list param_infos, int q, char *hex)
{
    for (int j = q - 1; j >= 0; j--) {
        my_putchar(hex[j]);
    }
}

int printf_xm(const char *format, va_list param_infos, int i, int compt)
{
    char hex[50];
    int q = 0;
    int k;
    int temp;

    k = (int) va_arg(param_infos, int);
    while (k != 0) {
        temp = 0;
        temp = k % 16;
        if (temp < 10) {
            hex[q] = temp + 48;
            q++;
        } else {
            hex[q] = temp + 55;
            q++;
        }
        k = k / 16;
    }
    printf_xxm(format, param_infos, q, hex);
    return (0);
}
