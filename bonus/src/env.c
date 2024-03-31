/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** env
*/


#include "../include/minishell.h"


int check_str(shell_t *shell, char **array)
{
    char *str = my_strdup(array[1]);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            print("setenv: Variable name must contain ");
            print("alphanumeric characters.\n");
            shell->status = 1;
            return 1;
        }
    }
    return 0;
}

void free_tab(shell_t *shell, char **fun)
{
    for (int i = 0; fun[i] != NULL; i++)
        free(fun[i]);
    free(fun);
}

static void envv_sett(shell_t *shell, struct list *head,
    struct list *new_node, char **array)
{
    char *env_temp = 0;

    env_temp = my_cat(array[1], "=");
    new_node->str = env_temp;
    new_node->str = my_cat(new_node->str, array[2]);
    new_node->next = NULL;
    if (shell->current == NULL) {
        shell->current = new_node;
    } else {
        head = shell->current;
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = new_node;
    }
}

static int fill_env(struct list *head, char **fun,
    struct list *new_node, char **array)
{
    char *temp_arg = NULL;
    char *temp_arg2 = NULL;

    while (head != NULL) {
        fun = my_str_to_word_array(head->str);
        if (strcmp_my(fun[0], array[1]) == 1) {
            temp_arg = my_cat(fun[0], "=");
            temp_arg2 = my_strdup(array[2]);
            temp_arg = my_cat(temp_arg, temp_arg2);
            head->str = temp_arg;
            free(temp_arg2);
            return 1;
        }
        head = head->next;
    }
    return 0;
}

static void env_set(shell_t *shell, char **env, char **fun, char **array)
{
    struct list *head = shell->current;
    struct list *new_node = malloc(sizeof(struct list));

    if (new_node == NULL)
        exit(84);
    if (fill_env(head, fun, new_node, array) == 0)
        envv_sett(shell, head, new_node, array);
    return;
}

static int arg_count(shell_t *shell, char **array)
{
    int counter = 0;

    for (int i = 0; array[i] != NULL; i++) {
        print("%s %i\n", array[i], i);
        counter++;
        if (strcmp_my(array[i], "|") == 1)
            break;
    }
    if (counter > 3) {
        print("setenv: Too many arguments.\n");
        shell->status = 1;
        return 1;
    }
    return 0;
}

void two_arg(shell_t *shell, char **env, char **array)
{
    char **fun = 0;

    if (check_str(shell, array) == 1)
        return;
    if (!(my_al(array[1][0]))) {
        print("setenv: Variable name must begin with a letter.\n");
        shell->status = 1;
        return;
    }
    env_set(shell, env, fun, array);
    shell->status = 0;
    return;
}

int set_env(shell_t *shell, char **env, char **array)
{
    if (arg_count(shell, array) == 1)
        return 1;
    if (array[0] != NULL && array[1] == NULL) {
        cmd_env(shell, env, array);
        shell->status = 0;
        return 0;
    }
    if (array[1] != NULL && array[2] == NULL) {
        if (!(my_al(array[1][0]))) {
            print("setenv: Variable name must begin with a letter.\n");
            shell->status = 1;
            return 1;
        }
        if (check_str(shell, array) == 1)
            return 1;
        env_alone(shell, env, array);
        shell->status = 0;
    } else
        two_arg(shell, env, array);
    return 0;
}

static void pwd_env(shell_t *shell, char **fun,
    char *temp_arg, struct list *head)
{
    char cwd[1024];

    if (str_my(fun[0], "PWD") == 1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            temp_arg = my_cat(fun[0], "=");
            temp_arg = my_realoc(temp_arg, cwd);
            temp_arg = my_cat(temp_arg, cwd);
            head->str = temp_arg;
            shell->status = 0;
            return;
        }
    }
}

void env_pwd(shell_t *shell)
{
    char **fun = 0;
    char *temp_arg = 0;
    struct list *head = shell->current;
    struct list *new_node = malloc(sizeof(struct list));

    if (new_node == NULL)
        exit(84);
    while (head != NULL) {
        fun = my_array(head->str);
        pwd_env(shell, fun, temp_arg, head);
        head = head->next;
    }
    return;
}
