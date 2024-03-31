/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** cd_comand
*/

#include "../include/minishell.h"
#include <errno.h>

static int count(shell_t *shell, char **array)
{
    int counter = 0;

    for (int i = 0; array[i] != NULL; i++)
        counter++;
    return counter;
}

static void cd_home(shell_t *shell, char *cwd, char **array)
{
    if (shell->home == NULL) {
        print("cd: No home directory.\n");
        shell->status = 1;
        return;
    }
    shell->oldpwd = my_strdup(cwd);
    chdir(shell->home);
    env_pwd(shell);
    shell->status = 0;
    return;
}

int handle(shell_t *shell, char **env, char *cwd, char **array)
{
    if (strcmp_my(array[1], "-") == 1 && array[1][1] == '\0') {
        if (shell->oldpwd != NULL) {
            chdir(shell->oldpwd);
            shell->oldpwd = my_strdup(cwd);
            env_pwd(shell);
            return 0;
        } else {
            print(": No such file or directory.\n");
            return 1;
        }
    } else {
        print("%s: No such file or directory.\n", array[1]);
        return 1;
    }
    return 0;
}

int perme_handler(shell_t *shell, char *cwd, char **array)
{
    struct stat path_stat;

    stat(array[1], &path_stat);
    if (access(array[1], R_OK) == -1) {
        print("%s/: Permission denied.\n", array[1]);
        shell->status = 1;
        return 1;
    }
    if (S_ISDIR(path_stat.st_mode) == 1) {
        shell->oldpwd = my_strdup(cwd);
        chdir(array[1]);
        env_pwd(shell);
        shell->status = 0;
        return 0;
    } else {
        print("%s: Not a directory.\n", array[1]);
        shell->status = 1;
        return 1;
    }
}

int cd_handler(shell_t *shell, char **env, char **array)
{
    char cwd[1024];
    int counter = count(shell, array);

    getcwd(cwd, sizeof(cwd));
    if (counter == 1 || strcmp_my(array[1], "~") == 1) {
        cd_home(shell, cwd, array);
        return 0;
    }
    if (shell->result == access(array[1], F_OK)) {
        if (perme_handler(shell, cwd, array) == 1)
            return 1;
        else
            return 0;
    }
    if (handle(shell, env, cwd, array) != 0) {
        shell->status = 1;
        return 1;
    }
    shell->status = 0;
    return 0;
}
