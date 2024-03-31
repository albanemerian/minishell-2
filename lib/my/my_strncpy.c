/*
** EPITECH PROJECT, 2023
** my_strncpy
** File description:
** my_strncpy
*/

#include "my.h"

char *change(const char *src, char *dest, int n)
{
    int i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}

char *my_strncpy(char *dest, char const *src, int n)
{
        change(src, dest, n);
        return (dest);
}
