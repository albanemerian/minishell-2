/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** my_strcat
*/

#include "my.h"

char *my_strcat(char *dest, char *src)
{
    int dest_len = 0;
    int src_len = 0;

    while (dest[dest_len] != '\0') {
        dest_len++;
    }
    while (src[src_len] != '\0') {
        src_len++;
    }
    for (int i = 0; i < src_len; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + src_len] = '\0';
    return dest;
}

char *my_cat(char *destination, char *source)
{
    int len_dest = my_strlen(destination);
    int len_src = my_strlen(source);
    char *res = malloc(sizeof(char) * (len_dest + len_src + 1));

    if (res == NULL) {
        exit(84);
    }
    my_strcpy(destination, res);
    my_strcpy(source, res + len_dest);
    return res;
}
