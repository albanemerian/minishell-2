/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** fork_pipe
*/

#include "../include/minishell.h"

static pid_t fork_child(int *pipefd, char **env, char **arr1, shell_t *shell)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        cat_cmd(shell, env, arr1);
        exit(0);
    }
    return pid;
}

static void exec_parent(shell_t *shell, char **env, char **arr2, int pipefd[2])
{
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    close(pipefd[1]);
    cat_cmd(shell, env, arr2);
    exit(0);
}

static void exec_pipe(shell_t *shell, char **env, char **arr1, char **arr2)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;
    char **dup = dup_arr(arr2);
    char *str = my_array_to_str(dup);

    if (pipe(pipefd) == -1) {
        exit(1);
    }
    pid1 = fork_child(pipefd, env, arr1, shell);
    if (find_if_simple_dir(shell, env, arr2, str) != 1) {
        pid2 = fork();
        if (pid2 == 0) {
            waitpid(pid1, NULL, 0);
            exec_parent(shell, env, arr2, pipefd);
        }
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid2, NULL, 0);
}

static int count_pipes(int num_pipes, char *line)
{
    int h = 0;

    while (line[h] != '\0') {
        if (line[h] == '|')
            num_pipes++;
        h++;
    }
    num_pipes += 1;
    return num_pipes;
}

static int get_simple_pipe(char **env, char *str, shell_t *shell)
{
    char *line1 = NULL;
    char *line2 = NULL;
    char **arr1 = NULL;
    char **arr2 = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
        line1 = my_strndup(str, i);
        line2 = my_strdup(str + i + 1);
        arr1 = fill_array(line1);
        arr2 = fill_array(line2);
        exec_pipe(shell, env, arr1, arr2);
        return 1;
        }
    }
    return 0;
}

static int handle_cd(char **array, shell_t *shell, char **env, int i)
{
    if (strcmp_my("cd", &array[i][0]) == 1) {
        if (cd_handler(shell, env, &array[i]) == 0)
            return 1;
    }
    return 0;
}

static int find_other_op(shell_t *shell, char **env, char **array, char *str)
{
    if (find_if_simple_dir(shell, env, array, str) != 0)
        return 1;
    if (is_left(shell, array, str, env) != 0)
        return 1;
    return 0;
}

int find_if_pipe(shell_t *shell, char **env, char **array, char *line)
{
    char *str = my_strdup(line);
    int num_pipes = 0;

    for (int i = 0; array[i] != NULL; i++) {
        if (handle_cd(array, shell, env, i) == 1)
            return 1;
    }
    num_pipes = count_pipes(num_pipes, line);
    if (num_pipes == 1) {
        if (get_simple_pipe(env, str, shell) == 1)
            return 1;
    }
    if (num_pipes > 1) {
        if (get_arg_multiple(shell, num_pipes, env, line) == 1)
            return 1;
    }
    if (find_other_op(shell, env, array, str) == 1)
        return 1;
    return 0;
}


//grep -oE '\b\w+\b' tata.txt | sort | uniq -c

//ls -l | grep .txt | wc -l
