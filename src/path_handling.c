/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** path_handling
*/

#include "../include/minishell.h"


void get_env(shell_t *shell)
{
    struct list *act = NULL;
    struct list *last = NULL;

    for (int i = 0; shell->env[i] != NULL; i++) {
        act = malloc(sizeof(struct list));
        if (act == NULL)
            exit(84);
        act->str = shell->env[i];
        act->next = NULL;
        if (shell->current == NULL)
            shell->current = act;
        if (last != NULL) {
            last->next = act;
        }
        last = act;
        act->next = NULL;
    }
}

void get_home(shell_t *shell)
{
    for (int i = 0; shell->env[i] != NULL; i ++) {
        if (str_my(shell->env[i], "HOME=") == 1) {
            shell->home = my_strdup(&shell->env[i][5]);
            break;
        }
    }
    for (int i = 0; shell->env[i] != NULL; i ++) {
        if (str_my(shell->env[i], "PATH=") == 1) {
            shell->path = my_strtok(&shell->env[i][5], ':');
            break;
        }
    }
    if (shell->path == NULL) {
        shell->path = malloc(sizeof(char *) * (3 + 1));
        shell->path[0] = my_strdup("/bin/");
        shell->path[1] = my_strdup("/usr/bin");
        shell->path[2] = NULL;
    }
    shell->oldpwd = NULL;
}

int env_length(char **env)
{
    int length = 0;

    while (env[length] != NULL) {
        length++;
    }
    return length;
}

void get_path(int argc, char **argv, char **env, shell_t *shell)
{
    int len = env_length(env);

    shell->env = malloc(sizeof(char *) * (len + 1));
    shell->path = NULL;
    shell->env_len = len;
    if (shell->env == NULL) {
        exit(84);
    }
    for (int i = 0; env[i] != NULL; i++) {
        shell->env[i] = malloc(sizeof(char) * (my_strlen(env[i]) + 1));
        shell->env[i] = my_strdup(env[i]);
        if (shell->env[i] == NULL) {
            exit(84);
        }
    }
    shell->env[env_length(env)] = NULL;
    get_home(shell);
    get_env(shell);
}
