/*
** EPITECH PROJECT, 2023
** my_revstr
** File description:
** my_revstr
*/

#include "my.h"

int *my_revstr(int argc, char **argv)
{
    char *c = 0;
    int i = 0;
    int length = argc - 1;

    for (int f = argc - 1; f > length / 2; f++) {
        c[length] = *argv[i];
        argv[i] = argv[f];
        *argv[f] = c[length];
        i = i + 1;
    }
    return (0);
}
