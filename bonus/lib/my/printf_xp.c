/*
** EPITECH PROJECT, 2023
** printf_xp
** File description:
** printf_xp
*/

#include <stdarg.h>
#include "my.h"

int printf_xxp(const char *format, va_list param_infos, int q, char *hex)
{
    for (int j = q - 1; j >= 0; j--) {
        my_putchar(hex[j]);
    }
}

int printf_xp(const char *format, va_list param_infos, int i, int compt)
{
    char hex[500];
    int q = 0;
    unsigned long int k;
    unsigned long int temp = 0;

    k = va_arg(param_infos, void *);
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
    printf_xxp(format, param_infos, q, hex);
    return (0);
}
