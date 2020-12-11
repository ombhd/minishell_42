# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 12:40:11 by obouykou          #+#    #+#              #
#    Updated: 2020/12/11 23:25:09 by obouykou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = $(wildcard ./*.c)

HEADER = ./libft.h

OBJECT = $(FILES:.c=.o)

OBJECT_B = $(FBONUS:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)
	@echo > /dev/null

$(NAME): $(OBJECT) $(HEADER)
	@ar -rcs $(NAME) $(OBJECT)

%.o:%.c	$(HEADER)					
	@gcc -c $< $(FLAGS) -o $@

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -rf $(NAME)

re : fclean all
