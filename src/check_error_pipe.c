/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** check_error_pipe
*/

#include "../include/minishell.h"

static int diff_built(char *str)
{
    if (strcmp_my(str, "env") != 1 && strcmp_my(str, "setenv") != 1 &&
        strcmp_my(str, "cd") != 1 && strcmp_my(str, "exit") != 1)
        return 0;
    return 1;
}

static int check_last_arg(shell_t *shell, char ***commands, int i, char *path)
{
    if (access(path, X_OK) == -1 && i == shell->num_commands - 1 &&
            diff_built(commands[i][0]) == 0 &&
            strcmp_my("./mysh", commands[i][0]) != 1) {
            print("%s: Command not found.\n", commands[i][0]);
            shell->status = 1;
            return 1;
    }
    return 0;
}

static int check(shell_t *shell, char ***commands, int fail, char **env)
{
    if (get_arg_multiple_two(shell, commands, env, shell->num_commands) == 1) {
        if (fail == 1)
            shell->status = fail;
        return 1;
    }
    return 0;
}

int use_arg_multiple(shell_t *shell, char ***commands, char **env,
    char *line)
{
    int fail = 0;
    char *str = NULL;
    char *path = NULL;

    for (int i = 0; commands[i] != NULL; i++) {
        if (commands[i][0][0] == '/')
            break;
        str = my_strdup(commands[i][0]);
        path = my_cat("/usr/bin/", str);
        if (check_last_arg(shell, commands, i, path) == 1)
            return 1;
        if (access(path, X_OK) == -1 && diff_built(commands[i][0]) == 0 &&
            strcmp_my("./mysh", commands[i][0]) != 1) {
            print("%s: Command not found.\n", commands[i][0]);
            fail = 1;
        }
    }
    if (check(shell, commands, fail, env) == 1)
        return 1;
    return 0;
}
