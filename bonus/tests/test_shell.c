/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** test_shell
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include <assert.h>

Test(error_handling, valid_input) {
    shell_t *shell = malloc(sizeof(shell_t)); 
    char *env[] = {"PATH=/bin", NULL};
    char *argv[] = {"program_name", NULL};
    int argc = 1;

    error_handling(shell, env, argv, argc);

    cr_assert_eq(shell->status, 0, "Status should be 0");
    free(shell);
}

Test(error_handling, valid_helper) {
    shell_t *shell = malloc(sizeof(shell_t)); 
    char *env[] = {"PATH=/bin", NULL};
    char *argv[] = {"program_name", "-h", NULL};
    int argc = 2;

    error_handling(shell, env, argv, argc);
    cr_assert_eq(shell->status, 0, "Status should be 0");
    free(shell);
}

Test(error_handling, valid_helpe) {
    shell_t *shell = malloc(sizeof(shell_t)); 
    char *env[] = {"PATH=/bin", NULL};
    char *argv[] = {"program_name", "--help", NULL};
    int argc = 2;

    error_handling(shell, env, argv, argc);
    cr_assert_eq(shell->status, 0, "Status should be 0");
    free(shell);
}

Test(error_handling, invalid_shell) {
    shell_t *shell = malloc(sizeof(shell_t)); 
    char *env[] = {"PATH=/bin", NULL};
    char *argv[] = {"program_name", "-frh", NULL};
    int argc = 2;

    error_handling(shell, env, argv, argc);
    cr_assert_eq(shell->status, 84, "Status should be 84");
    free(shell);
}

Test(error_handling, to_many_arg) {
    shell_t *shell = malloc(sizeof(shell_t)); 
    char *env[] = {"PATH=/bin", NULL};
    char *argv[] = {"program_name", "fsfsf", "jfsjf", NULL};
    int argc = 3;

    error_handling(shell, env, argv, argc);
    cr_assert_eq(shell->status, 84, "Status should be 84");
    free(shell);
}

