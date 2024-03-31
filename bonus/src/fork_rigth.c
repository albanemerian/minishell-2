/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** fork_directions
*/

#include "../include/minishell.h"

void move_str(char *str)
{
    int i = 0;
    int j = 0;
    int len = my_strlen(str);

    for (; i < len; i++) {
        if (str[i] != ' ')
            break;
    }
    if (i > 0) {
        for (; j < len - i; j++)
            str[j] = str[j + i];
        str[j] = '\0';
        len = my_strlen(str);
    }
    for (i = len - 1; i >= 0; i--) {
        if (str[i] != ' ')
            break;
    }
    if (i < len - 1)
        str[i + 1] = '\0';
}

static void look_for_error(shell_t *shell, int output_fd,
    char *output_filename)
{
    if (output_fd == -1) {
        print("%s: No such file or in fd directory.\n", output_filename);
        shell->status = 1;
        exit(1);
    }
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        shell->status = 1;
        exit(1);
    }
    close(output_fd);
}

void handle_file(int output_fd, char *output_filename, shell_t *shell)
{
    int open_flags = 0;

    if (output_filename != NULL) {
        move_str(output_filename);
        open_flags = O_WRONLY | O_CREAT |
            (shell->is_double ? O_APPEND : O_TRUNC);
        output_fd = open(output_filename, open_flags, S_IRUSR | S_IWUSR);
        look_for_error(shell, output_fd, output_filename);
    } else {
        print("%s: No such file or directory.\n", output_filename);
        shell->status = 1;
        exit(1);
    }
}

void execute_simp_dir(shell_t *shell, char **arr1, char *output_filename,
    char **env)
{
    pid_t pid = fork();
    int output_fd = 0;
    int status;

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        handle_file(output_fd, output_filename, shell);
        cat_cmd(shell, env, arr1);
        perror("execve");
        shell->status = 1;
        exit(1);
    } else {
        waitpid(pid, &status, 0);
    }
}

static int single_redir(shell_t *shell, char **env, int *i, char *line)
{
    char *line1 = NULL;
    char *line2 = NULL;
    char **arr1 = NULL;

    *i -= 1;
    line1 = my_strndup(line, *i);
    line2 = my_strdup(line + *i + 1);
    arr1 = fill_array(line1);
    shell->is_double = 0;
    execute_simp_dir(shell, arr1, line2, env);
    return 1;
}

static int double_redir(shell_t *shell, char **env, int *i, char *line)
{
    char *line1 = NULL;
    char *line2 = NULL;
    char **arr1 = NULL;

    (*i) -= 2;
    line1 = my_strndup(line, *i);
    (*i) += 3;
    line2 = my_strdup(line + *i);
    arr1 = fill_array(line1);
    shell->is_double = 1;
    execute_simp_dir(shell, arr1, line2, env);
    return 1;
}

int look_for_chev(shell_t *shell, char **env, int *i, char *line)
{
    if (line[*i] == '>') {
        (*i)++;
        if (line[*i] != '>') {
            return single_redir(shell, env, i, line);
        }
        if (line[*i] == '>') {
            return double_redir(shell, env, i, line);
        }
    }
    return 0;
}

int find_if_simple_dir(shell_t *shell, char **env, char **array, char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (look_for_chev(shell, env, &i, line) == 1) {
            shell->is_double = 2;
            return 1;
        }
    }
    shell->is_double = 2;
    return 0;
}
