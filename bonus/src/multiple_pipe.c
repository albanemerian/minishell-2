/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** multiple_pipe
*/

#include "../include/minishell.h"


void env_pipe(shell_t *shell, int i, int pipes[shell->num_commands - 1][2])
{
    int pipe_read_end = 0;
    int pipe_write_end = 0;

    pipe_read_end = pipes[i][0];
    pipe_write_end = pipes[i][1];
    close(pipe_read_end);
    dup2(pipe_write_end, STDOUT_FILENO);
    close(pipe_write_end);
}

int dup_pipes(int i, shell_t *shell, int pipes[shell->num_commands - 1][2],
    char ***commands)
{
    if (strcmp_my("env", commands[i][0]) == 1 ||
        strcmp_my("setenv", commands[i][0]) == 1) {
        env_pipe(shell, i, pipes);
        return 1;
    } else {
        if (i > 0)
            dup2(pipes[i - 1][0], STDIN_FILENO);
        if (i < shell->num_commands - 1)
            dup2(pipes[i][1], STDOUT_FILENO);
        for (int j = 0; j < shell->num_commands - 1; j++) {
            close(pipes[j][0]);
            close(pipes[j][1]);
        }
        return 0;
    }
}

void handle_left(char ***commands, int i, int k, shell_t *shell)
{
    int fd = open(commands[i][k + 1], O_RDONLY);

    if (fd == -1) {
        shell->status = 1;
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Error redirecting standard input");
        shell->status = 1;
        exit(1);
    }
    close(fd);
    exit(0);
}

int check_single_left(shell_t *shell, char ***commands, int i, int k)
{
    struct stat fileStat;

    if (strcmp_my(commands[i][k], "<") == 1) {
        if (stat(commands[i][k + 1], &fileStat) != 0) {
            print("%s: No such file or directory.\n", commands[i][k + 1]);
            shell->status = 1;
            return 84;
        }
        handle_left(commands, i, k, shell);
    }
    return 0;
}

static int exec_multiple_rigth(shell_t *shell, char ***commands, int i, int k)
{
    int fd = 0;
    char *file = NULL;

    if (i == shell->num_commands - 1 &&
        strcmp_my(commands[i][k], ">>") == 1) {
        file = my_strdup(commands[i][k + 1]);
        shell->is_double = 1;
        handle_file(fd, file, shell);
        shell->redir_stat = 1;
    }
    return fd;
}

int exec_redirections(char ***commands, int i, shell_t *shell)
{
    int fd = 0;
    char *file = NULL;

    for (int k = 0; commands[i][k] != NULL; k++) {
        if (check_single_left(shell, commands, i, k) == 84)
            return 84;
        if (i == shell->num_commands - 1 &&
            strcmp_my(commands[i][k], ">") == 1) {
            file = my_strdup(commands[i][k + 1]);
            shell->is_double = 0;
            handle_file(fd, file, shell);
            shell->redir_stat = 1;
        }
        fd = exec_multiple_rigth(shell, commands, i, k);
    }
    return fd;
}
