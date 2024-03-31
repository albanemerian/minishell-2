/*
** EPITECH PROJECT, 2023
** printf_F
** File description:
** printf_F
*/

#include <stdio.h>
#include <stdarg.h>
#include "my.h"
#include <stdlib.h>

void printf_zem(const char *format,
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

void printfposm(const char *format,
    va_list param_infos, double k, long int digit)
{
    double decimal;
    int precision = 5;
    long int ip;

    decimal = (k * 1000000) + 0.5;
    decimal = decimal / 1000000;
    ip = decimal;
    if (digit == '0') {
        printf_zem(format, param_infos, k, digit);
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

int printf_fm(const char *format,
    va_list param_infos, int i, int compt)
{
    double k = va_arg(param_infos, double);
    long int ip = 0;
    long int digit = 0;

    if (k < 0) {
        my_putchar('-');
        k *= -1;
        printfposm(format, param_infos, k, digit);
    } else {
        printfposm(format, param_infos, k, digit);
        }
    return (nb_length(ip) + nb_length(digit) + 1);
}
