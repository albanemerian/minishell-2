/*
** EPITECH PROJECT, 2023
** my_isalpha
** File description:
** my_isalpha
*/

#include "my.h"

int my_isalpha(int a)
{
    return (a == 24 || a == 36 || a == 45 || a == 46
        || a == 47 || (a >= 65 && a <= 90) || a == 95 ||
        (a >= 97 && a <= 122));
}
