# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhadraou <hhadraou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/19 21:59:29 by melalj            #+#    #+#              #
#    Updated: 2019/12/29 16:47:18 by hhadraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC = src/melalsh_main.c\
src/sighandler.c\
src/env.c\
src/func_env.c\
src/errors.c\
src/free.c\
src/readline.c\
src/ft_split.c\
src/echo.c\
src/helper.c\
src/dquote.c\
src/squote.c\
src/quote.c\
src/bs.c\
src/read_line.c\
src/exec.c\
src/parser.c\
src/refresh.c\
src/cmd.c\
parser_ab.c\
split_ab.c\
parser_lst.c\
red.c\
parser_error.c\
dup_fd.c\
src/type_builtin.c


all : $(NAME)

$(NAME) :
		@ make re -C ./libft
		@ make clean -C ./libft
		@ gcc src/main.c $(SRC) -g -ltermcap src/termcap/*.c libft/libft.a -o $(NAME)
		@ echo "\033[32m\033[1m$(NAME)\033[22m compiled && built successfully\033[0m"
		@ echo "\033[34m\033[1mdone \033[25m\033[0m"

clean :
		@ /bin/rm -f *.o

fclean : clean
		@ /bin/rm -f $(NAME)

re : fclean all clean
debug : fclean
		@ make re -C ./libft
		@ make clean -C ./libft
		@ gcc -g src/main.c $(SRC) -ltermcap src/termcap/*.c libft/libft.a -o $(NAME)-debug
		@ echo "\033[32m\033[1m$(NAME)\033[22m compiled && built successfully\033[0m"
		@ echo "\033[34m\033[1mdone \033[25m\033[0m"
