/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** my_realloc
*/

#include "my.h"

char *my_realoc(char *base, char *new)
{
    char *old = my_strdup(base);
    int old_size = my_strlen(base);
    int new_size = my_strlen(new);
    int total = old_size + new_size;
    char *resultat = NULL;

    free(base);
    resultat = malloc(sizeof(char) * (total + 1));
    resultat = old;
    return resultat;
}
