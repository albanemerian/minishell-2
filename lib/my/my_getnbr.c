/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** task05
*/

#include "my.h"

int is_number(char c)
{
    if (c >= '0' && c <= '9') {
        return (1);
    }
    return (0);
}

int my_sign(char c)
{
    if (c == '-') {
        return (1);
    }
    return (0);
}

int my_getnbr2(char const *str, char *chh, int finnum, int x)
{
    for (int n = 0; n < my_strlen(chh); n++) {
        finnum += chh[n] - '0';
        finnum *= 10;
    }
    finnum /= 10;
    if (x % 2 == 0) {
        return (finnum);
    }
    return (-1 * finnum);
}

int my_getnbr(char const *str)
{
    char chh[my_strlen(str)];
    int k = 0;
    int finnum = 0;
    int x = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        if (is_number(str[i]) == 1) {
            chh[k] = str[i];
            k++;
        }
        if (is_number(str[i]) == 0 && my_sign(str[i]) == 1) {
            x += 1;
        }
        if (k > 0 && is_number(str[i]) == 0) {
            break;
        }
    }
    chh[k] = '\0';
    return my_getnbr2(str, chh, finnum, x);
}
