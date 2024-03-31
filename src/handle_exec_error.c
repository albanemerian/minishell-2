/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** handle_exec_error
*/

#include "../include/minishell.h"

void handle_error(shell_t *shell, char **array)
{
    if (errno == ENOEXEC) {
        print("%s: Exec format error. ", array[0]);
        print("Wrong Architecture.\n");
        shell->status = 1;
        exit(1);
    }
    if (errno == EACCES) {
        print("%s: Permission denied.\n", array[0]);
        shell->status = 1;
        exit(1);
    }
    if (errno == ENOENT) {
        print("%s: Command not found.\n", array[0]);
        shell->status = 1;
        exit(1);
    }
}

void segfault_handler(shell_t *shell, int status)
{
    if (shell->status == 139)
        print("Segmentation fault\n");
    if (shell->status == 136)
        print("Floating exeption\n");
    if (shell->status == 134)
        print("Aborted\n");
    if (shell->status == 135)
        print("Bus error\n");
}

void check_singal(shell_t *shell, int status)
{
    if (WIFEXITED(status))
        shell->status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->status = 128 + WTERMSIG(status);
    segfault_handler(shell, status);
}
