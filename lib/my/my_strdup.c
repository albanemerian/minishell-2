/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** my_strdup
*/
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char *my_strdup(char const *src)
{
    int src_size = my_strlen(src);
    char *dest = malloc(sizeof(char) * (src_size + 1));
    int i = 0;

    if (dest == NULL)
        return NULL;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    if (dest == 0) {
        return (NULL);
    }
    dest[src_size] = '\0';
    return (dest);
}
