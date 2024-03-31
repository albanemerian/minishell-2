/*
** EPITECH PROJECT, 2024
** B-PSU-200-NAN-2-1-minishell1-albane.merian
** File description:
** my_malloc
*/

#include "my.h"


void my_memset(void *ptr, void *value, size_t num)
{
    unsigned char *p = ptr;

    for (size_t i = 0; i < num; ++i) {
        p[i] = (unsigned char)value;
    }
}

void *my_malloc(void *ptr, size_t size)
{
    size_t total_size = sizeof(ptr) * size;
    void *allocated_memory = malloc(total_size);

    if (allocated_memory == NULL) {
        return NULL;
    }
    if (ptr != NULL) {
        my_memset(allocated_memory, NULL, total_size);
    }
    return allocated_memory;
}
