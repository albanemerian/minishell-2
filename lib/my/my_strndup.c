/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** my_strndup
*/

#include "my.h"

char *my_strndup(char *src, int n)
{
    int i = 0;
    char *dest;
    size_t src_len = my_strlen(src);
    size_t copy_len = (src_len < n) ? src_len : n;

    dest = malloc(sizeof(char) * (copy_len + 1));
    if (dest == NULL) {
        return NULL;
    }
    for (i = 0; i < copy_len; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
