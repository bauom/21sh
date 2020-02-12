# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhadraou <haitamehadraoui@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 14:31:41 by hhadraou          #+#    #+#              #
#    Updated: 2019/07/29 00:55:17 by melalj           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ./*.c

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
	@gcc -c $(FLAGS) $(SRC)
	@ar rc $(NAME) *.o
	@echo "\033[32mlibft compiled && built successfully\033[0m"

clean : 
	@/bin/rm -f *.o

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
