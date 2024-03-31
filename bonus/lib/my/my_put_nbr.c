/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** task07
*/

#include <unistd.h>

static void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_put_nbr(int n)
{
    int i;

    if (n < 0) {
        my_putchar('-');
        n *= (-1);
    }
    if (n >= 0) {
        i = n % 10;
        if (n > 9) {
            n /= 10;
            my_put_nbr(n);
            my_putchar('0' + i);
        } else {
            my_putchar(n + '0');
        }
    }
}
