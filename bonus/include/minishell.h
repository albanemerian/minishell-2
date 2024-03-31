/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** minishell
*/

#include "struct.h"
#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <dirent.h>
#include <stddef.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#ifndef MINISHELL_H_
    #define MINISHELL_H_

int set_env(shell_t *shell, char **env, char **array);
int cmd_env(shell_t *shell, char **env, char **array);
void error_handling(shell_t *shell, char **env, char **argv, int argc);
void get_path(int argc, char **argv, char **env, shell_t *shell);
int cd_handler(shell_t *shell, char **env, char **array);
void option(shell_t *shell);
int exit_func(shell_t *shell, char **env, char **array);
int unset_env(shell_t *shell, char **env, char **array);
char **my_array(const char *str);
int last_exec(shell_t *shell, char **env);
int env_alone(shell_t *shell, char **env, char **array);
void env_pwd(shell_t *shell);
char **list_to_array(shell_t *shell, char **env);
void free_tab(shell_t *shell, char **fun);
int check_str(shell_t *shell, char **array);
int find_directions(shell_t *shell);
int last_exeve(shell_t *shell, pid_t pid, char **envp);
void handle_error(shell_t *shell, char **array);
void segfault_handler(shell_t *shell, int status);
void check_singal(shell_t *shell, int status);
void cmd_handler(shell_t *shell, char **envp, char *str_z, char **array);
void not_full_path(shell_t *shell, char **envp, char *str_z, char **array);
void get_new_path(shell_t *shell, char **envp);
int is_empty(shell_t *shell);
int find_if_pipe(shell_t *shell, char **env, char **array, char *line);
void execute_simp_dir(shell_t *shell, char **arr1, char *output_filename,
    char **env);
int find_if_simple_dir(shell_t *shell, char **env, char **array, char *line);
void cat_cmd(shell_t *shell, char **env, char **arr);
char **fill_array(char *str1);
int is_left(shell_t *shell, char **array, char *line, char **env);
void move_str(char *str);
int get_arg_multiple(shell_t *shell, int num_pipes, char **env, char *line);
void handle_file(int output_fd, char *output_filename, shell_t *shell);
int single_left_redir(shell_t *shell, char **env, int *i, char *line);
void cmd_cat(shell_t *shell, char **env, char **arr);
int dup_pipes(int i, shell_t *shell, int pipes[shell->num_commands - 1][2],
    char ***commands);
int exec_redirections(char ***commands, int i, shell_t *shell);

#endif /* !MINISHELL_H_ */
