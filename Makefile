##
## EPITECH PROJECT, 2023
## my_lib
## File description:
## my_lib
##

CC	=	gcc

NAME	=	mysh

UNIT_TEST	= test

CFLAGS	=	-g -Wshadow -Werror -Wall -I./include

FLCRIT 	=  -I./include

CRITFLAG	=	tests/test_lib.c tests/test_shell.c --coverage -lcriterion

LIBS	=	-L./ -lmy

TEST_LIBS	=	-L./ -lmy

SRC		=   main.c	\
			src/helper.c	\
			src/env.c	\
			src/error_handling.c	\
			src/path_handling.c		\
			src/cd_comand.c		\
			src/option_handler.c	\
			src/fork_usage.c		\
			src/unset_env.c			\
			src/exit.c				\
			src/set_env_solo.c		\
			src/list_to_array.c		\
			src/handle_dir.c		\
			src/handle_exec_error.c	\
			src/fork_pipe.c			\
			src/fork_rigth.c		\
			src/fork_left.c			\
			src/cat_cmd.c			\
			src/multiple_pipe.c		\
			src/mulitiple_pipe_two.c	\
			src/check_error_pipe.c

SRCTEST	= 	src/helper.c	\
			src/env.c	\
			src/error_handling.c	\
			src/path_handling.c		\
			src/cd_comand.c		\
			src/option_handler.c	\
			src/fork_usage.c		\
			src/unset_env.c			\
			src/exit.c				\
			src/set_env_solo.c		\
			src/list_to_array.c		\
			lib/my/my_put_nbr.c			\
			lib/my/my_putstr.c				\
			lib/my/my_strlen.c				\
			lib/my/my_unsigned_nbr.c 		\
			lib/my/my_putchar.c 			\
			lib/my/my_positive_nbr.c 		\
			lib/my/my_getnbr.c				\
			lib/my/my_isnum.c 				\
			lib/my/my_strdup.c 			\
			lib/my/my_strcat.c 			\
			lib/my/my_revstr.c 			\
			lib/my/my_printf.c 			\
			lib/my/printf_i.c 				\
			lib/my/printf_c.c 				\
			lib/my/printf_d.c 				\
			lib/my/printf_s.c 				\
			lib/my/printf_u.c 				\
			lib/my/printf_x.c 				\
			lib/my/printf_xm.c 			\
			lib/my/printf_o.c 				\
			lib/my/printf_f.c 				\
			lib/my/printf_fm.c 			\
			lib/my/printf_cross.c 			\
			lib/my/printf_l.c	 			\
			lib/my/my_isalpha.c 			\
			lib/my/my_strncpy.c	 		\
			lib/my/my_strcpy.c 			\
			lib/my/my_strstr.c 			\
			lib/my/my_strcmp.c 			\
			lib/my/my_is_even.c			\
			lib/my/my_strtok.c				\
			lib/my/my_str_to_word_array.c	\
			lib/my/my_charcmp.c			\
			lib/my/my_array.c				\
			lib/my/my_realloc.c			\
			lib/my/my_alpha.c

OBJ		=	$(SRC:.c=.o)

all:	libmy $(NAME)

$(NAME):	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)
			@echo -e "\e[1;32m{ Makefile is ready }\e[00;37m"
			@echo -e "\e[1;36m{ Binary is ready }\e[00;37m"
			@cp -f $(NAME) tests/
			@echo -e "\e[1;35m{ ./mysh copied in tester }\e[00;37m"

$(UNIT_TEST): libmy
			$(CC) -o $(UNIT_TEST) $(SRCTEST) $(FLCRIT) $(CRITFLAG) $(TEST_LIBS)

tests_run:	$(UNIT_TEST)
			@./$(UNIT_TEST)
			@gcovr --exclude tests/

.PHONY: libmy

libmy:
	$(MAKE) -C lib/my

norm:
	@make clean
	@make fclean
	@coding-style . .
	@cat coding-style-reports.log

clean:
			$(MAKE) -C lib/my clean
			@rm -f $(OBJ)
			@rm -f *.gc*
			@rm -f coding-style-reports.log
			@rm -f *~
			@rm -f *.gcda
			@rm -f *.gcno
			@rm -f libmy.a

fclean:	clean
			$(MAKE) -C lib/my fclean
			@rm -f $(NAME)
			@rm -f $(UNIT_TEST)
			@echo -e "\e[1;33m{ REPOSITORIE as been cleaned }\e[00;37m"


re:	fclean all
