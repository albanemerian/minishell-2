/*
** EPITECH PROJECT, 2023
** B-PSU-100-NAN-1-1-sokoban-albane.merian
** File description:
** my_strstr
*/

#include "my.h"
#include <string.h>

char *my_strstr(const char *str, int c)
{
    while (*str != '\0') {
        if (*str == c) {
            return ((char *)str);
        }
        str++;
    }
    return NULL;
}
