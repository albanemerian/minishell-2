/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** helper
*/

#include "../include/my.h"

int helper(int argc)
{
    print("\x1B[1;36m\nUsage:\n");
    print("./minishell [OPTION]:\n");
    print("\t -h\n\t --help\n");
    print("In case of error the program returns: 84\n");
    print("\nThis terminal is an equivalent to a tsch\n");
    print("It should recreate the exact beahvior of a tsch terminal");
    print(" with limited action\n\x1B[00;37m");
    exit(0);
}
