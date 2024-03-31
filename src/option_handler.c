/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** option_handler
*/

#include "../include/minishell.h"


int (*fm[6])(struct shell_s *, char **, char **) = {
    &cmd_env, &exit_func, &cd_handler, &set_env, &unset_env};

void fill_str(shell_t *shell)
{
    char *fun = my_strdup(shell->l);
    char *token = strtok(fun, " \t\n");
    int i = 0;
    int j = 0;
    char *sleep = NULL;

    while (token != NULL) {
        i++;
        token = strtok(NULL, " \t\t");
    }
    shell->str = my_malloc(sleep, (i + 1));
    sleep = strtok(shell->l, " \t\n");
    while (sleep != NULL) {
        shell->str[j] = my_strdup(sleep);
        j++;
        sleep = strtok(NULL, " \t\n");
    }
    free(fun);
    shell->str[i] = NULL;
}

int is_empty(shell_t *shell)
{
    if (shell->l == NULL)
        return 1;
    for (int i = 0; shell->l[i] != '\0'; i++) {
        if (shell->l[i] != ' ' && shell->l[i] != '\t') {
            return 0;
        }
    }
    return 1;
}

static int exec_builtin(shell_t *shell, char **envp, char **dups)
{
    char *flag_m[5] = {"env", "exit", "cd", "setenv", "unsetenv"};

    for (int index = 0; index < 5; index++) {
        if (strcmp_my(shell->str[0], flag_m[index]) == 1) {
            fm[index](shell, envp, dups);
            return 1;
        }
    }
    return 0;
}

void option(shell_t *shell)
{
    char **envp = list_to_array(shell, shell->env);
    char *line = NULL;
    char **dups = NULL;

    shell->result = 0;
    if (is_empty(shell) == 1)
        return;
    fill_str(shell);
    dups = dup_arr(shell->str);
    line = my_array_to_str(dups);
    if (find_directions(shell) == 1)
        return;
    if (find_if_pipe(shell, shell->env, shell->str, line) != 0)
        return;
    if (exec_builtin(shell, envp, dups) == 1)
        return;
    last_exec(shell, envp);
}
