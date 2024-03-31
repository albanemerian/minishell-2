/*
** EPITECH PROJECT, 2023
** printf_f
** File description:
** printf_f
*/

#include <stdio.h>
#include <stdarg.h>
#include "my.h"
#include <stdlib.h>

void printf_ze(const char *format,
    va_list param_infos, double k, long int digit)
{
    double decimal = 0;
    int precision = 5;
    long int ip = k;

    decimal = k -ip;
    my_put_nbr(ip);
    my_putchar('.');
        for (int n = 0; n <= precision; n++) {
            decimal *= 10;
            digit = (decimal + 0.5);
            my_put_nbr(digit);
            decimal -= (digit);
    }
}

void printfpos(const char *format,
    va_list param_infos, double k, long int digit)
{
    double decimal;
    int precision = 5;
    long int ip;

    decimal = (k * 1000000) + 0.5;
    decimal = decimal / 1000000;
    ip = decimal;
    if (digit == '0') {
        printf_ze(format, param_infos, k, digit);
    } else {
        decimal = decimal - ip;
        my_put_nbr(ip);
        my_putchar('.');
        for (int f = 0; f <= precision; f++) {
            decimal *= 10;
            digit = (decimal);
            my_positive_nbr(digit);
            decimal -= digit;
        }
    }
}

int printf_f(const char *format,
    va_list param_infos, int i, int compt)
{
    double k = va_arg(param_infos, double);
    long int ip = 0;
    long int digit = 0;

    if (k < 0) {
        my_putchar('-');
        k *= -1;
        printfpos(format, param_infos, k, digit);
    } else {
        printfpos(format, param_infos, k, digit);
        }
    return (nb_length(ip) + nb_length(digit) + 1);
}
