/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** unset_env
*/

#include "minishell.h"


void unset_envv(shell_t *shell, char **fun, int i, char **array)
{
    struct list *head = shell->current;
    struct list *previous = NULL;

    while (head != NULL) {
        fun = my_array(head->str);
        if (strcmp_my(fun[0], array[i]) == 1) {
            previous->next = head->next;
            return;
        } else {
        previous = head;
        head = head->next;
        }
    }
    return;
}

int unset_env(shell_t *shell, char **env, char **array)
{
    char **fun = 0;

    if (array[1] == NULL) {
        print("unsetenv: Too few arguments.\n");
        shell->status = 1;
        return 0;
    }
    for (int i = 0; array[i] != NULL; i++)
        unset_envv(shell, fun, i, array);
    return 0;
}
