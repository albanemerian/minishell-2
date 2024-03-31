/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** handle_fir
*/

#include "../include/minishell.h"

int (*fm_dir[6])(struct shell_s *, char **, char **) = {
    &cmd_env, &exit_func, &cd_handler, &set_env, &unset_env};

static void check_perms(shell_t *shell, char **arr)
{
    struct stat path_stat;

    stat(arr[0], &path_stat);
    if ((S_ISDIR(path_stat.st_mode) == 1) && arr[0][0] != '.')
        print("%s: Permission denied.\n", arr[0]);
    else
        handle_error(shell, arr);
    shell->status = EXIT_FAILURE;
    exit(EXIT_FAILURE);
}

int multiple_exec(shell_t *shell, char **envp, char **array)
{
    char *dup = my_strdup(array[0]);
    char **arr = my_strtok(dup, ' ');
    int status = 0;
    char *str_z = NULL;

    if (strcmp_my(arr[0], "") == 1)
        shift_array(arr);
    str_z = my_strdup(arr[0]);
    if (shell->pid == 0) {
        cmd_handler(shell, envp, str_z, arr);
        check_perms(shell, arr);
    } else {
        wait(&status);
        check_singal(shell, status);
    }
    return 1;
}

int last_execve(shell_t *shell, char **array, char *line)
{
    char **envp = list_to_array(shell, shell->env);

    get_new_path(shell, envp);
    if (find_if_pipe(shell, envp, array, line) != 0)
        return 1;
    shell->pid = fork();
    if (shell->pid < 0)
        return 1;
    if (multiple_exec(shell, envp, array) == 1)
        return 1;
    return 0;
}

static void put_in_triple(shell_t *shell, int num_commas)
{
    int index = 0;
    char *token = strtok(shell->new_l, ";");

    shell->all_dups = (char ***)my_malloc
        (shell->all_dups, (num_commas + 1) * sizeof(char **));
    while (token != NULL) {
        shell->all_dups[index] = (char **)my_malloc
            (shell->all_dups[index], sizeof(char *));
        shell->all_dups[index][0] = my_strndup(token, my_strlen(token));
        index++;
        token = strtok(NULL, ";");
    }
    shell->all_dups[index] = NULL;
}

void option_dir(shell_t *shell, int i, char **array)
{
    char *flag_m[6] = {"env", "exit", "cd", "setenv", "unsetenv"};
    char *dup = my_strdup(array[0]);
    char **arr = my_strtok(dup, ' ');

    if (strcmp_my(arr[0], "") == 1)
        shift_array(arr);
    if (is_empty(shell) == 1)
        return;
    for (int index = 0; index <= 6; index++) {
        if (strcmp_my(arr[0], flag_m[index]) == 1) {
            fm_dir[index](shell, shell->env, arr);
            return;
        }
    }
    last_execve(shell, shell->all_dups[i], dup);
}

void print_char(shell_t *shell)
{
    for (int i = 0; shell->all_dups[i] != NULL; i++) {
        option_dir(shell, i, shell->all_dups[i]);
    }
}

int find_directions(shell_t *shell)
{
    int num_commas = 0;

    shell->dup = dup_arr(shell->str);
    shell->new_l = my_array_to_str(shell->dup);
    for (int i = 0; shell->new_l[i] != '\0'; i++) {
        if (shell->new_l[i] == ';')
            num_commas++;
    }
    if (num_commas != 0) {
        put_in_triple(shell, num_commas);
        print_char(shell);
        return 1;
    } else
        shell->new_l = NULL;
    return 0;
}
