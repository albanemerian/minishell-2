/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** error_handling
*/

#include "../include/minishell.h"

void error_handling(shell_t *shell, char **env, char **argv, int argc)
{
    shell->status = 0;
    if (shell == NULL)
        exit(84);
    if (env == NULL)
        exit(84);
    if (argc == 2) {
        if (!(strcmp_my(argv[1], "-h") ||
            strcmp_my(argv[1], "--help") == 1)) {
                shell->status = 84;
                exit(0);
        } else {
            helper(argc);
        }
    } else if (argc > 2) {
        shell->status = 84;
        exit(0);
    }
    get_path(argc, argv, env, shell);
}
