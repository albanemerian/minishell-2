/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** mulitiple_pipe_two
*/

#include "../include/minishell.h"


static void close_pipes_redir(shell_t *shell,
    int pipes[shell->num_commands - 1][2], int fd)
{
    for (int i = 0; i < shell->num_commands - 1; i++) {
        close(pipes[i][1]);
        close(pipes[i][0]);
    }
    for (int i = 0; i < shell->num_commands; i++)
        wait(NULL);
    if (fd != STDOUT_FILENO) {
        if (dup2(fd, STDOUT_FILENO) == -1) {
            exit(1);
        }
    }
}

static void close_pipes(shell_t *shell, int pipes[shell->num_commands - 1][2],
    int fd)
{
    for (int i = 0; i < shell->num_commands - 1; i++) {
        close(pipes[i][1]);
        close(pipes[i][0]);
    }
    for (int i = 0; i < shell->num_commands; i++)
        wait(NULL);
}

int check_for_builtin(char ***commands, shell_t *shell, char **env, int i)
{
    if (strcmp_my("cd", commands[i][0]) == 1 && i == shell->num_commands) {
        if (cd_handler(shell, env, commands[i]) == 0)
            return 1;
    }
    if (strcmp_my("exit", commands[i][0]) == 1 && i == shell->num_commands - 1)
        exit_func(shell, env, commands[i]);
    return 0;
}

static void exec_all(shell_t *shell, char ***commands, int i, char **env)
{
    pid_t pid = fork();

    if (pid == -1)
        exit(1);
    if (pid == 0) {
        if (dup_pipes(i, shell, shell->pipes, commands) == 1) {
            cmd_env(shell, env, commands[i]);
            exit(0);
        } else {
            if (strcmp_my("grep", commands[i][0]) == 1) {
                execlp("grep", "grep", "--color=always", commands[i][1], NULL);
                perror("execlp");
                exit(1);
            }
            cmd_cat(shell, env, commands[i]);
        }
    }
}

static void handle_closing(shell_t *shell, int fd)
{
    if (shell->redir_stat == 1)
        close_pipes_redir(shell, shell->pipes, fd);
    else
        close_pipes(shell, shell->pipes, fd);
}

int exec_multiple_pipes(shell_t *shell, char **env, char ***commands)
{
    int fd = 0;

    shell->redir_stat = 0;
    for (int i = 0; i < shell->num_commands - 1; i++) {
        if (pipe(shell->pipes[i]) == -1) {
            shell->status = 1;
            exit(1);
        }
    }
    for (int i = 0; i < shell->num_commands; i++) {
        check_for_builtin(commands, shell, env, i);
        fd = exec_redirections(commands, i, shell);
        if (fd == 84)
            break;
        exec_all(shell, commands, i, env);
    }
    handle_closing(shell, fd);
    return 1;
}

static int get_arg_multiple_two(shell_t *shell, char ***commands, char **env,
    int num_pipes)
{
    int i = 0;

    shell->num_commands = 0;
    for (; commands[i] != NULL; i++);
    if (i <= num_pipes - 1) {
        print("Invalid null command.\n");
        shell->status = 1;
        return 1;
    }
    shell->num_commands = num_pipes;
    if (exec_multiple_pipes(shell, env, commands) == 1)
        return 1;
    return 0;
}

int get_arg_multiple(shell_t *shell, int num_pipes, char **env, char *line)
{
    char ***commands = NULL;
    int f = 0;
    char *dup = NULL;
    char *token = NULL;

    commands = (char ***)my_malloc(NULL, (num_pipes + 1) * sizeof(char **));
    token = strtok(line, "|");
    while (token != NULL) {
        commands[f] = (char **)my_malloc(NULL, sizeof(char *));
        move_str(token);
        dup = my_strdup(token);
        commands[f] = my_strtok(dup, ' ');
        f++;
        token = strtok(NULL, "|");
    }
    commands[f] = NULL;
    if (get_arg_multiple_two(shell, commands, env, num_pipes) == 1)
        return 1;
    return 0;
}
