/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell2-albane.merian
** File description:
** move_array
*/

#include "my.h"

void shift_array(char **arr)
{
    int i;

    for (i = 0; arr[i] != NULL; i++) {
        arr[i] = arr[i + 1];
    }
}
