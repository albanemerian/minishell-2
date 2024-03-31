/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** fork_left
*/

#include "../include/minishell.h"

static int single_left_two(int input_fd, char *line, int *i)
{
    char *line2 = NULL;

    line2 = my_strdup(line + *i + 1);
    move_str(line2);
    input_fd = open(line2, O_RDONLY);
    if (input_fd == -1) {
        print("%s: No such file or directory.\n", line2);
        return 1;
    }
    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("Error redirecting standard input");
        return 1;
    }
    close(input_fd);
    return input_fd;
}

int single_left_redir(shell_t *shell, char **env, int *i, char *line)
{
    char *line1 = NULL;
    char **arr1 = NULL;
    int input_fd = 0;
    int status = 0;
    pid_t pid = fork();

    if (pid == -1)
        exit(1);
    if (pid == 0) {
        *i -= 1;
        line1 = my_strndup(line, *i);
        arr1 = fill_array(line1);
        input_fd = single_left_two(input_fd, line, i);
        cmd_cat(shell, env, arr1);
        exit(shell->status);
    } else
        waitpid(pid, &status, 0);
    return 1;
}

static void get_lines(shell_t *shell, char **env, char **arr1, char *line2)
{
    char *l = NULL;
    size_t len = 0;
    ssize_t read = 0;

    while (1) {
        print("? ");
        read = getline(&l, &len, stdin);
        if (l[read - 1] == '\n')
            l[read - 1] = '\0';
        if (read == -1 || strcmp_my(l, line2) == 1)
            cat_cmd(shell, env, arr1);
    }
}

static int double_left_redir(shell_t *shell, char **env, int *i, char *line)
{
    char *line1 = NULL;
    char *line2 = NULL;
    char **arr1 = NULL;
    pid_t pid = fork();
    int status = 0;

    *i -= 2;
    line1 = my_strndup(line, *i);
    *i += 4;
    line2 = my_strdup(line + *i);
    arr1 = fill_array(line1);
    if (pid == -1)
        exit(1);
    if (pid == 0)
        get_lines(shell, env, arr1, line2);
    else
        waitpid(pid, &status, 0);
    return 1;
}

int look_for_left_chev(shell_t *shell, char **env, int *i, char *line)
{
    shell->status = 0;
    if (line[*i] == '<') {
        (*i)++;
        if (line[*i] != '<') {
            return single_left_redir(shell, env, i, line);
        }
        if (line[*i] == '<') {
            return double_left_redir(shell, env, i, line);
        }
    }
    return 0;
}

int is_left(shell_t *shell, char **array, char *line, char **env)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (look_for_left_chev(shell, env, &i, line) == 1) {
            return 1;
        }
    }
    return 0;
}
