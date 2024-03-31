/*
** EPITECH PROJECT, 2024
** mini-shell-1
** File description:
** struct
*/

#include <stdlib.h>

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct array_s {

    int counter;
    char **array;
    int ind;
    int length;
    const char *start;
    int len;
} array_t;

#endif /* !STRUCT_H_ */
