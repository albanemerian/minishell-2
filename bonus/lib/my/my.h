/*
** EPITECH PROJECT, 2023
** my_lib
** File description:
** my_lib
*/
#include <stdarg.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef MY_LIB
    #define MY_LIB
void my_putchar(char c);
void my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
void my_unsigned_nbr(unsigned int n);
void my_positive_nbr(int nb);
int my_isalpha(int a);
int my_isnum(char *nb);
char *my_strdup(char const *src);
char *my_strcat(char *dest, char *src);
void print(const char *format, ...);
int *my_revstr(int argc, char **argv);
int printf_d(const char *format, va_list param_infos, int i, int compt);
int printf_i(const char *format, va_list param_infos, int i, int compt);
int printf_s(const char *format, va_list param_infos, int i, int compt);
int printf_c(const char *format, va_list param_infos, int i, int compt);
int printf_o(const char *format, va_list param_infos, int i, int compt);
int printf_u(const char *format, va_list param_infos, int i, int compt);
int printf_x(const char *format, va_list param_infos, int i, int compt);
int printf_xm(const char *format, va_list param_infos, int i, int compt);
int printf_f(const char *format, va_list param_infos, int i, int compt);
int printf_fm(const char *format, va_list param_infos, int i, int compt);
int printf_cross(const char *format, va_list param_infos, int i, int compt);
int printf_l(const char *format, va_list param_infos, int i, int compt);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strcpy(const char *src, char *dest);
char *my_strstr(const char *str, int c);
int my_strcmp(char const *s1, char const *s2);
int strcmp_my(char const *s1, char const *s2);
int my_is_even(int nb);
int my_cmp(char const *s1, char const *s2);
int my_getnbr(char const *str);
int cmp_my(char const *s1, char const *s2);
int nb_length(int n);
char **my_strtok(const char *str, char separator);
char **my_str_to_word_array(const char *str);
int str_my(char const *s1, char const *s2);
int my_char(char s1, char s2);
char *my_cat(char *destination, char *source);
char *my_realoc(char *base, char *new_size);
int my_al(int a);
void *my_malloc(void *ptr, size_t size);
void my_memset(void *ptr, void *value, size_t num);
char **my_array_and(const char *str);
char *my_array_to_str(char **strings);
char **dup_arr(char **strings);
char *my_strndup(char *src, int n);
void shift_array(char **array);
int get_array_size(char **array);
char **dup_arra(char **source, int size);
size_t my_len(const char *str);
char *my_cpy(char *dest, const char *src);
char **my_tok(char *line, char *delim);

#endif /* !my_lib */
