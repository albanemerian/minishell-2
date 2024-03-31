/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** fork_usage
*/

#include "minishell.h"

static void check_architecture(shell_t *shell)
{
    if (errno == ENOEXEC) {
        if (shell->str[0][0] != '.')
            print("%s: Command not found.\n", shell->str[0]);
        else {
            print("%s: Exec format error. ", shell->str[0]);
            print("Wrong Architecture.\n");
        }
        shell->status = 1;
        exit(1);
    }
}

static void check_ls_for_color(shell_t *shell)
{
    int j = 1;

    if (my_strcmp(shell->str[0], "ls") == 1) {
        for (; shell->str[j] != NULL; j++);
        shell->str = realloc(shell->str, (j + 2) * sizeof(char *));
        if (shell->str == NULL) {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }
        shell->str[j] = "--color=auto";
        shell->str[j + 1] = NULL;
    }
    if (my_strcmp(shell->str[0], "echo") == 1) {
        if (my_strcmp(shell->str[1], "$?") == 1) {
            print("%i\n", shell->status);
            shell->status = 0;
            exit(0);
        }
    }


}

void cmd_handler(shell_t *shell, char **envp, char *str_z, char *str)
{
    char *dup_path = NULL;

    check_ls_for_color(shell);
    if (access(shell->str[0], X_OK) == 0) {
        if (execve(shell->str[0], shell->str, envp) != -1) {
            free(str_z);
            exit(EXIT_FAILURE);
        }
        check_architecture(shell);
    }
    for (int i = 0; shell->path[i] != NULL; i++) {
        dup_path = my_strdup(shell->path[i]);
        str = my_cat(dup_path, "/");
        str = my_cat(str, str_z);
        if (access(str, F_OK) == 0) {
            execve(str, shell->str, envp);
            free(str_z);
            exit(EXIT_FAILURE);
        }
        free(dup_path);
    }
}

static void segfault_handler(shell_t *shell, int status)
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

static void check_singal(shell_t *shell, int status)
{
    if (WIFEXITED(status))
        shell->status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->status = 128 + WTERMSIG(status);
    segfault_handler(shell, status);
}

int exec_last(shell_t *shell, pid_t pid, char **envp, char *str)
{
    char *str_z = my_strdup(shell->str[0]);
    struct stat path_stat;
    int status;

    stat(shell->str[0], &path_stat);
    if (pid == 0) {
        cmd_handler(shell, envp, str_z, str);
        if ((S_ISDIR(path_stat.st_mode) == 1) && shell->str[0][0] != '.' && shell->str[0][0] == '/')
            print("%s: Permission dggdenied.\n", shell->str[0]);
        else
            print("%s: Command not found.\n", shell->str[0]);
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
    char *str = NULL;
    char **envp = list_to_array(shell, env);
    pid_t pid = fork();

    get_new_path(shell, envp);
    if (pid < 0)
        return 1;
    if (exec_last(shell, pid, envp, str) == 1)
        return 1;
    return 0;
}
static void check_architecture(shell_t *shell)
{
    if (errno == ENOEXEC) {
        if (shell->str[0][0] != '.')
            print("%s: Command not found.\n", shell->str[0]);
        else {
            print("%s: Exec format error. ", shell->str[0]);
            print("Wrong Architecture.\n");
        }
        shell->status = 1;
        exit(1);
    }
}
