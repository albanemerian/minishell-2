/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** commas_handler
*/

#include "../include/minishell.h"

int last_exeve(shell_t *shell, pid_t pid, char **envp)
{
    char *str_z = my_strdup(shell->str[0]);
    struct stat path_stat;
    int status = 0;

    stat(shell->str[0], &path_stat);
    if (pid == 0) {
        cmd_handler(shell, envp, str_z, shell->str);
        if ((S_ISDIR(path_stat.st_mode) == 1) && shell->str[0][0] != '.')
            print("%s: Permission denied.\n", shell->str[0]);
        else
            handle_error(shell, shell->str);
        shell->status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    } else {
        wait(&status);
        check_singal(shell, status);
    }
    return 1;
}
