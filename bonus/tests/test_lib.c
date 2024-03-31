/*
** EPITECH PROJECT, 2023
** B-PSU-100-NAN-1-1-sokoban-albane.merian
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test (nbr, test_1, .init = redirect_all_std)
{
    int nb = 50;
    char *output = "50";

    my_put_nbr(nb); 
    cr_assert_stdout_eq_str(output);

}
Test(mini_prints, string_char, .init = redirect_all_std)
{

    print("Hello %s.", "world");
    cr_assert_stdout_eq_str("Hello world.");
}

Test(mini_printd, string_char, .init = redirect_all_std)
{
    print("Hello your age is %d.", 23);
    cr_assert_stdout_eq_str("Hello your age is 23.");
}

Test(mini_printi, string_char, .init = redirect_all_std)
{
    int nb = 43;
    
    print("If you multiple %d by %d, the result is %i.", nb, 2, nb * 2);
    cr_assert_stdout_eq_str("If you multiple 43 by 2, the result is 86.");
}

Test(mini_printmod, string_char, .init = redirect_all_std)
{
    print("The %%%s%% is fun.", "world");
    cr_assert_stdout_eq_str("The %world% is fun.");
}

Test(mini_printlen, string_char, .init = redirect_all_std)
{
    char str [8] = "Ronflex";
    
    print("%s is a %i character word.",str, my_strlen(str));
    cr_assert_stdout_eq_str("Ronflex is a 7 character word.");
}

Test(mini_printeror, string_char, .init = redirect_all_std)
{
    print("The world is %.");
    cr_assert_stdout_eq_str("The world is Invalid flags.");
}

Test(mini_printevery, string_char, .init = redirect_all_std)
{
    int bn = 36;
    char str [20] = "Epitech";

    print("If you leave %s at %d years old you spent %i years of your life there.", str, bn, my_strlen(str));
    cr_assert_stdout_eq_str("If you leave Epitech at 36 years old you spent 7 years of your life there.");
}

Test(mini_printfun, string_char, .init = redirect_all_std)
{
    print("Staying alive is %s, and great %.", "fun");
    cr_assert_stdout_eq_str("Staying alive is fun, and great Invalid flags.");
}

Test(mini_printf_nb, string_char, .init = redirect_all_std)
{
    print("Staying alive my ass %d.", -32);
    cr_assert_stdout_eq_str("Staying alive my ass -32.");
}

Test(mini_printfd, string_char, .init = redirect_all_std)
{
    print("The world is fin %d.", 34);
    cr_assert_stdout_eq_str("The world is fin 34.");
}

Test(mini_printo, string_char, .init = redirect_all_std)
{
    print("The octal value o is %o.", 150);
    cr_assert_stdout_eq_str("The octal value o is 226.");

}

Test(mini_printoo, string_char, .init = redirect_all_std)
{
    print("The octal value of o %o.", 244);
    cr_assert_stdout_eq_str("The octal value of o 364.");
}

Test(mini_printuu, string_char, .init = redirect_all_std)
{
    unsigned int nb = 123405;
    
    print("The absolute value of %u.", nb);
    cr_assert_stdout_eq_str("The absolute value of 123405.");
}

Test(mini_printuaze, string_char, .init = redirect_all_std)
{
    unsigned int bn = 5678789;

    print("The absolute value of %u.", bn);
    cr_assert_stdout_eq_str("The absolute value of 5678789.");
}

Test(mini_printfghg, string_char, .init = redirect_all_std)
{
    float i = 2.35;

    print("The float value of lower f is %f.", i);
    cr_assert_stdout_eq_str("The float value of lower f is 2.350000.");
}

Test(mini_printfvu, string_char, .init = redirect_all_std)
{
    print("The absolute float f is %f.", 4.2);
    cr_assert_stdout_eq_str("The absolute float f is 4.200000.");
}

Test(mini_printfdj, string_char, .init = redirect_all_std)
{
    float j = 10.13;

    print("The upper value is F %f.", j);
    cr_assert_stdout_eq_str("The upper value is F 10.130000.");
}

Test(mini_printfa, string_char, .init = redirect_all_std)
{
    print("The hexa value in lower is %x.", 11);
    cr_assert_stdout_eq_str("The hexa value in lower is b.");
}

Test(mini_printff, string_char, .init = redirect_all_std)
{
    print("The hexa value lower %x %x.", 20, 55);
    cr_assert_stdout_eq_str("The hexa value lower 14 37.");
}

Test(mini_printfup, string_char, .init = redirect_all_std)
{
    print("The hexa value upper %X %X %X.", 11, 20, 55);
    cr_assert_stdout_eq_str("The hexa value upper B 14 37.");
}

Test(mini_printfchf, string_char, .init = redirect_all_std)
{
    print("The unique of a character%c.", 's');
    cr_assert_stdout_eq_str("The unique of a characters.");
}

Test(mini_printFupper, string_char, .init = redirect_all_std)
{
    float n = 2.35;
    
    print("The upper case value of F is %F.", n);
    cr_assert_stdout_eq_str("The upper case value of F is 2.350000.");
}

Test(mini_printFgh, string_char, .init = redirect_all_std)
{
    print("%f", 4.123456789);
    cr_assert_stdout_eq_str("4.123457");
}

Test(mini_printuppF, string_char, .init = redirect_all_std)
{
    print("The return value of F upper %f.", 214748.34);
    cr_assert_stdout_eq_str("The return value of F upper 214748.340000.");
}

Test(mini_printupperneg, string_char, .init = redirect_all_std)
{
    float r = -10.13;

    print("The value upper of a negative is %F.", r);
    cr_assert_stdout_eq_str("The value upper of a negative is -10.130000.");
}


Test(printlowz, string_char, .init = redirect_all_std)
{
    print("The value is %f.", 214748.31);
    cr_assert_stdout_eq_str("The value is 214748.310000.");
}

Test(my_printzer, string_char, .init = redirect_all_std)
{
    print("%f", 4.123456789);
    cr_assert_stdout_eq_str("4.123457");
}

Test(my_printze, string_char, .init = redirect_all_std)
{
    print("The limit %f, %F.", -21474836.478, -21474836.478);
    cr_assert_stdout_eq_str("The limit -21474836.478000, -21474836.478000.");
}

Test(my_printund, string_char, .init = redirect_all_std)
{
    print("%f %F.", -456861114.1111516, -456861114.1111516);
    cr_assert_stdout_eq_str("-456861114.111152 -456861114.111152.");
}
Test(printnull, string_char, .init = redirect_all_std)
{
    print("%f %F", -42, -42);
    cr_assert_stdout_eq_str("0.000000 0.000000");
}

Test(printthth, string_char, .init = redirect_all_std)
{
    print("%f %F", 0.913, 0.913);
    cr_assert_stdout_eq_str("0.913000 0.913000");
}

Test(printzefi, string_char, .init = redirect_all_std)
{
    print("%f %F", 42.05, 42.05);
    cr_assert_stdout_eq_str("42.050000 42.050000");
}

Test(printcroh, string_char, .init = redirect_all_std)
{
    print("%#o", 23);
    cr_assert_stdout_eq_str("027");
}

Test(my_printroon, string_char, .init = redirect_all_std)
{
    print("%#x", 23);
    cr_assert_stdout_eq_str("0x17");
}

Test(printcroom, string_char, .init = redirect_all_std)
{
    print("%#X", 23);
    cr_assert_stdout_eq_str("0X17");
}

Test(printcrou, string_char, .init = redirect_all_std)
{
    print("%#d", 34);
    cr_assert_stdout_eq_str("34");
}

Test(printcrod, string_char, .init = redirect_all_std)
{
    print("%#f %#F", 23.435, 23.435);
    cr_assert_stdout_eq_str("23.435000 23.435000");
}

Test(printcrs, string_char, .init = redirect_all_std)
{
    print("%#s", "epitech");
    cr_assert_stdout_eq_str("epitech");
}

Test(printcrc, string_char, .init = redirect_all_std)
{
    char i ='a';
    
    print("%#c", i);
    cr_assert_stdout_eq_str("a");
}

Test(printcru, string_char, .init = redirect_all_std)
{
    unsigned int bns = 123405;
    
    print("%#u", bns);
    cr_assert_stdout_eq_str("123405");
}

Test(printcris, string_char, .init = redirect_all_std)
{
    char str [8] = "Ronflex";

    print("%#s is a %#i character word.",str, my_strlen(str));
    cr_assert_stdout_eq_str("Ronflex is a 7 character word.");
}

Test(printcrmod, string_char, .init = redirect_all_std)
{
    print("The value %#%%s%% is fun.", "world");
    cr_assert_stdout_eq_str("The value %world% is fun.");
}

Test(my_isalpha_o, uppercase_letters) {
    cr_assert_eq(my_isalpha('A'), 1);
    cr_assert_eq(my_isalpha('Z'), 1);
}

Test(my_isalpha_u, lowercase_letters) {
    cr_assert_eq(my_isalpha('a'), 1);
    cr_assert_eq(my_isalpha('z'), 1);
}

Test(my_isalpha_n, non_letters) {
    cr_assert_eq(my_isalpha('0'), 0);
    cr_assert_eq(my_isalpha('#'), 0);
    cr_assert_eq(my_isalpha('\n'), 0);
}

Test(my_positive_nbr, single_digit_numbers, .init = redirect_all_std) {
    my_positive_nbr(5);
    cr_assert_stdout_eq_str("5");
}


Test ( my_strcat, test_strcat)
{
    char dest[5] = "guys";

    cr_assert_str_eq(my_cat(dest, "Hello"),strcat(dest, "Hello"));
}

Test(str_functions, my_strdup_returns_correct_string)
{
    const char *source = "hello";
    char *duplicate = my_strdup(source);

    cr_assert_str_eq(duplicate, "hello", "Duplicate should be equal to 'hello'");
    free(duplicate);
}

Test(str_functions, my_strstr_finds_character) {
    const char *str = "hello";
    int c = 'e';

    char *result = my_strstr(str, c);

    cr_assert_not_null(result, "Character 'e' should be found in 'hello'");
    cr_assert_str_eq(result, "ello", "Result should point to 'ello' in 'hello'");
}

Test(str_functions, my_strstr_handles_character_not_found) {
    const char *str = "hello";
    int c = 'z';

    char *result = my_strstr(str, c);
    cr_assert_null(result, "Character 'z' should not be found in 'hello'");
}
