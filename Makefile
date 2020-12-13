# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/08 13:24:31 by obouykou          #+#    #+#              #
#    Updated: 2020/06/08 13:24:31 by obouykou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = libminishell.a

LIBFT = ./libft/libft.a

MS_MAIN = minishell.c

FILES = ./srcs/command/cd.c ./srcs/command/commands.c ./srcs/command/exec_cmd.c \
		./srcs/command/echo.c ./srcs/command/env.c ./srcs/command/error.c \
		./srcs/command/exit.c ./srcs/command/export.c ./srcs/command/pwd.c \
		./srcs/command/redir_fds.c ./srcs/command/unset.c ./srcs/parsing/clean_ex.c \
		./srcs/parsing/delimeters_parser.c ./srcs/parsing/get_next_line.c ./srcs/parsing/get_next_line_utils.c \
		./srcs/parsing/helpers.c ./srcs/parsing/init.c ./srcs/command/child_process.c \
		./srcs/parsing/parse.c ./srcs/parsing/parse_split.c ./srcs/parsing/parse_total_cmds.c \
		./srcs/parsing/parse_vars.c ./srcs/parsing/skip_chars_parse.c ./srcs/parsing/get_input.c \
		./srcs/parsing/parsing_secured.c 
		
HEADER = ./includes/minishell.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)
	@echo "\n\033[32m◊◊◊ ------- Minishell has been created successfully ------- ◊◊◊\033[0m\n"

$(NAME): $(OBJECT) $(HEADER) $(FILES)
	@ar -rcs $(LIB) $(OBJECT)
	@echo "\n\033[36m◊◊◊ Producin' object files done! ◊◊◊\033[0m\n"
	@cd ./libft && make -s
	@echo "\n\033[36m◊◊◊ Producin' libft done! ◊◊◊\033[0m\n"
	@gcc $(FLAGS) $(MS_MAIN) $(LIB) $(LIBFT) -o $(NAME)

%.o:%.c $(HEADER)								
	@gcc -c $< $(FLAGS) -o $@

clean:
	@cd ./libft && make -s fclean
	@rm -rf $(OBJECT) $(LIB)
	@echo "\n\033[36m◊◊◊ Cleanin' object files done! ◊◊◊\033[0m\n"

fclean: clean
	@rm -rf $(NAME)

re : fclean all
