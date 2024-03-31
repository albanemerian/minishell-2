/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** mulitiple_pipe_two
*/

#include "../include/minishell.h"

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

static void handle_close(shell_t *shell, int pipes[shell->num_commands - 1][2],
    int i)
{
    for (i = 0; i < shell->num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    for (i = 0; i < shell->num_commands; i++) {
        wait(NULL);
    }
    if (dup2(shell->fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
}

static void handle_pipes(shell_t *shell, int pipes[shell->num_commands - 1][2],
    int i)
{
    if (i != 0) {
        if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (i != shell->num_commands - 1) {
        if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < shell->num_commands - 1; j++) {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
}

static void create_pipes(int i, shell_t *shell,
    int pipes[shell->num_commands - 1][2])
{
    for (i = 0; i < shell->num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
}

static int fork_pipe(shell_t *shell, int i, char ***commands,
    int pipes[shell->num_commands - 1][2])
{
    pid_t pid = fork();

    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0) {
        if (strcmp_my("env", commands[i][0]) == 1 ||
            strcmp_my("setenv", commands[i][0]) == 1) {
            env_pipes(shell, i, pipes);
            cmd_env(shell, shell->envp, commands[i]);
            return 3;
        }
        handle_pipes(shell, pipes, i);
        cmd_cat(shell, shell->envp, commands[i]);
    }
    return 0;
}

int exec_multiple_pipes(shell_t *shell, char **env, char ***commands)
{
    int fd = 0;
    int i = 0;
    int pipes[shell->num_commands - 1][2];

    shell->envp = dup_arr(env);
    create_pipes(i, shell, pipes);
    for (i = 0; i < shell->num_commands; i++) {
        check_for_builtin(commands, shell, env, i);
        fd = exec_redirections(commands, i, shell);
        if (fd == 84)
            break;
        if (fork_pipe(shell, i, commands, pipes) == 3)
            break;
    }
    handle_close(shell, pipes, i);
    shell->envp = NULL;
    return 1;
}

static void check_for_wrong(char ***commands, int i, int j, shell_t *shell)
{
    if (i < (shell->num_commands - 1) && (strcmp_my(commands[i][j], ">") == 1
        || strcmp_my(commands[i][j], ">>") == 1)) {
            print("Ambiguous output redirect.\n");
            shell->status = 1;
            exit(1);
        }
    if (strcmp_my(commands[i][j], ">") == 1 ||
        strcmp_my(commands[i][j], ">>") == 1) {
        j++;
        if (commands[i][j] == NULL) {
            print("Missing name for redirect.\n");
            shell->status = 1;
            exit(1);
        }
    }
}

int get_arg_multiple_two(shell_t *shell, char ***commands, char **env,
    int num_pipes)
{
    int i = 0;

    shell->fd = 0;
    shell->fd = dup(STDOUT_FILENO);
    for (; commands[i] != NULL; i++) {
        for (int j = 0; commands[i][j] != NULL; j++) {
            check_for_wrong(commands, i, j, shell);
        }
    }
    if (i <= num_pipes - 1) {
        print("Invalid null command.\n");
        shell->status = 1;
        exit(1);
    }
    shell->redir_stat = 0;
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
    if (use_arg_multiple(shell, commands, env, line) == 1)
        return 1;
    return 0;
}
