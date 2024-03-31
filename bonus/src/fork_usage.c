/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** fork_usage
*/

#include "minishell.h"


// static void move_end_arr(char **array)
// {
//     for (int i = 0; array[i] != NULL; i++) {
//         if (array[i][0] == '\0') {
//             array[i] = array[i + 1];
//             array[i + 1] = NULL;
//             break;
//         }
//     }
// }


static void check_architecture(shell_t *shell, char **array)
{
    if (errno == ENOEXEC) {
        if (array[0][0] != '.')
            print("%s: Command not found.\n", array[0]);
        else {
            print("%s: Exec format error. ", array[0]);
            print("Wrong Architecture.\n");
        }
        shell->status = 1;
        exit(1);
    }
}
// void not_full_path(shell_t *shell, char **envp, char *str_z, char **array)
// {
//     char *dup_path = NULL;
//     char *str = NULL;

    
//     for (int i = 0; shell->path[i] != NULL; i++) {
//         dup_path = my_strdup(shell->path[i]);
//         str = my_cat(dup_path, "/");
//         str = my_cat(str, str_z);
//         if (access(str, F_OK) == 0) {
//             execve(str, array, envp);
//             free(str_z);
//             exit(EXIT_FAILURE);
//         }
//         free(dup_path);
//     }
// }

static void handle_echo(shell_t *shell, char **array)
{
    if (my_strcmp(array[0], "echo") == 1) {
        if (my_strcmp(array[1], "$?") == 1) {
            print("%i\n", shell->status);
            shell->status = 0;
            exit(0);
        }
    }
}

static char **check_ls_for_color(shell_t *shell, char **array)
{
    int j = 1;

     {
        for (; array[j] != NULL; j++);
        array = realloc(array, (j + 2) * sizeof(char *));
        if (array == NULL) {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }
        array[j] = "--color=auto";
        array[j + 1] = NULL;
        return array;
    }
    return NULL;
}

void not_full_path(shell_t *shell, char **envp, char *str_z, char **array)
{
    char *dup_path = NULL;
    char *str = NULL;

    handle_echo(shell, array);
    if (my_strcmp(array[0], "ls") == 1)
        array = check_ls_for_color(shell, array);
    if (access(array[0], X_OK) == 0) {
        if (execve(array[0], array, envp) != -1) {
            free(str_z);
            exit(EXIT_FAILURE);
        }
        check_architecture(shell, array);
    }
    for (int i = 0; shell->path[i] != NULL; i++) {
        dup_path = my_strdup(shell->path[i]);
        str = my_cat(dup_path, "/");
        str = my_cat(str, str_z);
        if (access(str, F_OK) == 0) {
            execve(str, array, envp);
            free(str_z);
            exit(EXIT_FAILURE);
        }
        free(dup_path);
    }
}


void cmd_handler(shell_t *shell, char **envp, char *str_z, char **array)
{
    if (execve(array[0], array, envp) != -1) {
        free(str_z);
        exit(EXIT_FAILURE);
    }
    if (errno == ENOENT) {
        not_full_path(shell, envp, str_z, array);
    } else {
        handle_error(shell, array);
    }
}

int exec_last(shell_t *shell, char **envp)
{
    char *str_z = my_strdup(shell->str[0]);
    struct stat path_stat;
    int status = 0;

    stat(shell->str[0], &path_stat);
    if (shell->pid == 0) {
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

void get_new_path(shell_t *shell, char **envp)
{
    for (int i = 0; envp[i] != NULL; i ++) {
        if (str_my(envp[i], "PATH=") == 1) {
            shell->path = my_strtok(&envp[i][5], ':');
            return;
        }
    }
    shell->path[0] = my_strdup("/usr/bin");
    shell->path[1] = my_strdup("/bin");
    shell->path[2] = my_strdup("/usr/local/bin");
    shell->path[3] = my_strdup("/usr/sbin");
    shell->path[4] = NULL;
}

int last_exec(shell_t *shell, char **env)
{
    char **envp = list_to_array(shell, env);
    char *line = NULL;

    get_new_path(shell, envp);
    shell->dup = dup_arr(shell->str);
    line = my_array_to_str(shell->dup);
    if (find_if_pipe(shell, envp, shell->str, line) != 0) {
        return 1;
    }
    shell->pid = fork();
    if (shell->pid < 0)
        return 1;
    if (exec_last(shell, envp) == 1) {
        wait(&shell->pid);
        return 1;
    }
    return 0;
}
