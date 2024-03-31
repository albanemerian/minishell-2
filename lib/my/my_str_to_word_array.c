/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** my_str_to_word_array
*/

#include "my.h"
#include "struct.h"
#include <stdbool.h>

char **words_counter(const char *str)
{
    int counter = 1;
    char **array;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=')
            counter++;
    }
    array = malloc((counter + 1) * sizeof(char *));
    if (array == NULL)
        return NULL;
    array[counter] = NULL;
    return array;
}

void midlles_words(array_t *a, const char *str, int i)
{
    if (a->start < str + i) {
        a->length = i - (a->start - str) + 1;
        a->array[a->ind] = malloc((a->length + 1) * sizeof(char));
        my_strncpy(a->array[a->ind], a->start, a->length);
        a->array[a->ind][a->length - 1] = '\0';
        a->ind++;
    }
}

void lasts_line(array_t *a, const char *str)
{
    a->length = my_strlen(a->start);
    a->array[a->ind] = malloc((a->length + 1) * sizeof(char));
    my_strncpy(a->array[a->ind], a->start, a->length);
    a->array[a->ind][a->length] = '\0';
}

char **my_str_to_word_array(const char *str)
{
    array_t *a = malloc(sizeof(array_t));

    a->array = words_counter(str);
    a->start = str;
    a->len = my_strlen(str);
    a->ind = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            midlles_words(a, str, i);
            a->start = str + i + 1;
        }
    }
    lasts_line(a, str);
    return a->array;
}
