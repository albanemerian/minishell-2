/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** cat_cmd
*/

#include "../include/minishell.h"

char **fill_array(char *str1)
{
    char **array = NULL;
    char *fun = my_strdup(str1);
    char *token = strtok(fun, " \0");
    int i = 0;
    int j = 0;
    char *sleep = NULL;

    while (token != NULL) {
        i++;
        token = strtok(NULL, " \0");
    }
    array = my_malloc(sleep, (i + 1));
    sleep = strtok(str1, " \0");
    while (sleep != NULL) {
        array[j] = my_strdup(sleep);
        j++;
        sleep = strtok(NULL, " \0");
    }
    array[i] = NULL;
    return array;
}

static char **get_new_arr(char **arr, char **dup, char *str, int j)
{
    char *new = NULL;
    int i = j;
    int f = i + 1;

    if (str[j] == '>' || str[j] == '<' || (str[j] == '>' &&
        str[f] == '>')) {
        new = my_strndup(str, j);
        for (int k = 0; arr[k] != NULL; k++)
            free(arr[k]);
        free(arr);
        arr = my_tok(new, " \0");
    }
    return arr;
}

void cat_cmd(shell_t *shell, char **env, char **arr)
{
    char *path = NULL;
    char **dup = dup_arr(arr);
    char *str = my_array_to_str(dup);

    for (int j = 0; str[j] != '\0'; j++)
        arr = get_new_arr(arr, dup, str, j);
    for (int i = 0; shell->path[i] != NULL; i++) {
        path = my_cat(shell->path[i], "/");
        path = my_cat(path, arr[0]);
        if (access(path, X_OK) == 0) {
            execve(path, arr, env);
            exit(1);
        }
    }
    print("Command '%s' not found\n", arr[0]);
    shell->status = 1;
    exit(1);
}

void exec_cmd(shell_t *shell, char **env, char **arr)
{
    char *path = NULL;

    for (int i = 0; shell->path[i] != NULL; i++) {
        path = my_cat(shell->path[i], "/");
        path = my_cat(path, arr[0]);
        if (access(path, X_OK) == 0) {
            execve(path, arr, env);
            exit(1);
        }
    }
}

void cmd_cat(shell_t *shell, char **env, char **arr)
{
    char **dup = dup_arr(arr);
    char *str = my_array_to_str(dup);

    if (execve(arr[0], arr, env) != -1) {
        exit(EXIT_FAILURE);
    }
    for (int j = 0; str[j] != '\0'; j++)
        arr = get_new_arr(arr, dup, str, j);
    if (errno == ENOENT) {
        exec_cmd(shell, env, arr);
        print("%s: Command not found.\n", arr[0]);
        shell->status = 1;
        exit(1);
    }
}
