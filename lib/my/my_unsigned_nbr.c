/*
** EPITECH PROJECT, 2023
** my_unsigned_nbr
** File description:
** my_unsigned_nbr
*/
#include <unistd.h>
#include "my.h"

void my_unsigned_nbr(unsigned int n)
{
    int i = 0;

    if (n >= 0) {
        i = n % 10;
        if (n > 9) {
            n /= 10;
            my_unsigned_nbr(n);
            my_putchar('0' + i);
        } else {
            my_putchar(n + '0');
        }
    }
}
