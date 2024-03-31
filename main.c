/*
** EPITECH PROJECT, 2024
** Updated lib
** File description:
** main
*/

#include "include/minishell.h"

void free_func(shell_t *shell)
{
    if (shell->l != NULL) {
        free(shell->l);
        shell->l = NULL;
    }
    if (shell->str != NULL) {
        for (int i = 0; shell->str[i] != NULL; i++) {
            free(shell->str[i]);
            shell->str[i] = NULL;
        }
        free(shell->str);
        shell->str = NULL;
    }
}

void handle_ctrl_d(shell_t *shell)
{
    if (shell->read == -1) {
        if (shell->status >= 256)
            shell->status /= 256;
        exit(shell->status);
    }
}

static void without_a_pip(shell_t *shell, char **env, char *cwd)
{
    shell->len = 0;
    shell->read = getline(&shell->l, &shell->len, stdin);
    handle_ctrl_d(shell);
    if (shell->l[shell->read - 1] == '\n')
        shell->l[shell->read - 1] = '\0';
    option(shell);
    free_func(shell);
}

static char *cwd_parser(char *cwd, shell_t *shell)
{
    int counter = 0;
    char *mal = NULL;
    char *path_dup = my_strdup(cwd);
    char *token = strtok(path_dup, "/");
    char **path = NULL;

    path = my_malloc(mal, 100);
    while (token != NULL) {
        path[counter] = my_strdup(token);
        counter++;
        token = strtok(NULL, "/");
    }
    if (strcmp_my(cwd, "/") == 1) {
        path[0] = cwd;
        path[1] = NULL;
        return path[0];
    }
    return path[counter - 1];
}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));
    char cwd[1024];
    char *path;

    error_handling(shell, env, argv, argc);
    while (1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            path = cwd_parser(cwd, shell);
            print("[mini-shell@ %s]$ ", path);
        }
        without_a_pip(shell, env, cwd);
    }
    if (shell->status >= 256)
        shell->status /= 256;
    return (shell->status);
}
