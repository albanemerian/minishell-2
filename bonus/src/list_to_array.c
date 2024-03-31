/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** list_to_array
*/

#include "minishell.h"

int len_array(shell_t *shell)
{
    int i = 0;
    struct list *list = shell->current;

    while (list != NULL) {
        i++;
        list = list->next;
    }
    return i;
}

char **list_to_array(shell_t *shell, char **env)
{
    char *mal = NULL;
    char **array = my_malloc(mal, (shell->env_len + 1));
    int i = 0;
    int len = len_array(shell);
    struct list *list = shell->current;

    for (; env[i] != NULL; i++)
        array[i] = malloc(sizeof(env[i]));
    i = 0;
    while (list != NULL) {
        array[i] = list->str;
        i++;
        list = list->next;
    }
    array[len] = NULL;
    return array;
}
