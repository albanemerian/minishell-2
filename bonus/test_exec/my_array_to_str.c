/*
** EPITECH PROJECT, 2024
** mini-shell-2
** File description:
** my_array_to_str
*/

#include "my.h"

char *str_to_array(char *result, int total_length, char **strings, int index)
{
    result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; strings[i] != NULL; i++) {
        strcpy(&result[index], strings[i]);
        index += strlen(strings[i]);
        if (strings[i+1] != NULL) {
            result[index++] = ' ';
        }
    }
    return result;
}

char *array_to_str(char **strings)
{
    int total_length = 0;
    char *result = NULL;
    int index = 0;

    for (int i = 0; strings[i] != NULL; i++) {
        total_length += strlen(strings[i]);
        if (strings[i+1] != NULL) {
            total_length++;
        }
    }
    str_to_array(result, total_length, strings, index);
    result[index] = '\0';
    return result;
}
