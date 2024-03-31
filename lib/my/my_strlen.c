/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** task03 - chgt putchar -> return
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stddef.h>

size_t my_len(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int my_strlen(char const *str)
{
    int c = 0;

    if (str == NULL) {
        return (84);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        c += 1;
    }
    return (c);
}
