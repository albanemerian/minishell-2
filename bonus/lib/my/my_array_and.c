/*
** EPITECH PROJECT, 2024
** mini-shell-2
** File description:
** my_array_and
*/

#include "my.h"
#include "struct.h"

char **wor_counter(const char *str)
{
    int counter = 0;
    char **array;

    for (int i = 0; str[i] != '\0'; i++) {
        if (strcmp_my(&str[i], "&&") == 1)
            counter++;
    }
    array = (char **)malloc((counter + 1) * sizeof(char *));
    if (array == NULL)
        return NULL;
    return array;
}

void midll_words(array_t *a, const char *str, int i)
{
    if (a->start < str + i) {
        a->length = i - (a->start - str) + 1;
        a->array[a->ind] = (char *)malloc((a->length + 1) * sizeof(char));
        my_strncpy(a->array[a->ind], a->start, a->length);
        a->array[a->ind][a->length - 1] = '\0';
        a->ind++;
    }
}

void las_line(array_t *a, const char *str)
{
    a->length = my_strlen(a->start);
    a->array[a->ind] = (char *)malloc((a->length + 1) * sizeof(char));
    my_strcpy(a->start, a->array[a->ind]);
    a->array[a->ind][a->length + 1] = '\0';
}

char **my_array_and(const char *str)
{
    array_t *a = malloc(sizeof(array_t));

    a->ind = 0;
    a->array = wor_counter(str);
    a->start = str;
    a->len = my_strlen(str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '&' && str[i + 1] == '&') {
            midll_words(a, str, i);
            a->start = str + i + 2;
        }
    }
    las_line(a, str);
    a->array[a->ind + 1] = NULL;
    return a->array;
}
