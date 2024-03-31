/*
** EPITECH PROJECT, 2023
** B-MUL-100-NAN-1-1-myradar-albane.merian
** File description:
** my_str_to_word_array
*/

#include "my.h"
#include "struct.h"
#include <string.h>

char **my_tok(char *line, char *delim)
{
    char *fun = my_strdup(line);
    char *token = strtok(fun, delim);
    int i = 0;
    int j = 0;
    char **array = NULL;
    char *sleep = NULL;

    while (token != NULL) {
        i++;
        token = strtok(NULL, delim);
    }
    array = my_malloc(sleep, (i + 1));
    sleep = strtok(line, delim);
    while (sleep != NULL) {
        array[j] = my_strdup(sleep);
        j++;
        sleep = strtok(NULL, delim);
    }
    array[i] = NULL;
    return array;
}

static char **word_counter(const char *str, char separator)
{
    int counter = 1;
    char **array;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator)
            counter++;
    }
    array = malloc((counter + 1) * sizeof(char *));
    if (array == NULL)
        return NULL;
    array[counter] = NULL;
    return array;
}

void midlle_words(array_t *a, const char *str, int i)
{
        a->length = i - (a->start - str) + 1;
        a->array[a->ind] = malloc((a->length + 1) * sizeof(char));
        my_strncpy(a->array[a->ind], a->start, a->length);
        a->array[a->ind][a->length - 1] = '\0';
        a->ind++;
}

void last_line(array_t *a, const char *str)
{
    a->length = my_strlen(a->start);
    a->array[a->ind] = malloc((a->length + 1) * sizeof(char));
    my_strncpy(a->array[a->ind], a->start, a->length);
    a->array[a->ind][a->length] = '\0';
}

char **my_strtok(const char *str, char separator)
{
    array_t *a = malloc(sizeof(array_t));

    a->array = word_counter(str, separator);
    a->start = str;
    a->len = my_strlen(str);
    a->ind = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator) {
            midlle_words(a, str, i);
            a->start = str + i + 1;
        }
    }
    last_line(a, str);
    a->array[a->ind + 1] = NULL;
    return a->array;
}
