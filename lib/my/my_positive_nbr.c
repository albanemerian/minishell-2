/*
** EPITECH PROJECT, 2023
** my_positive_nbr
** File description:
** my_positive_nbr
*/

#include <unistd.h>
#include "my.h"

void my_positive_nbr(int nb)
{
    int i = 0;

    if (nb >= 0) {
        i = nb % 10;
        if (nb > 9) {
            nb /= 10;
            my_positive_nbr(nb);
            my_putchar('0' + i);
        } else {
            my_putchar(nb + '0');
        }
    }
}
