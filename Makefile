# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 17:10:37 by bshintak          #+#    #+#              #
#    Updated: 2022/11/10 18:50:11 by bshintak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -fsanitize=address
INCLUDE		=	-I ~/.brew/opt/readline/include -lreadline
MKD			=	mkdir
RM			=	rm -f

SRC_NAME	=	main.c				\
				find_builtin.c		\
				pwd.c				\
				echo.c				\
				cd.c				\
				parser.c			\
				get_env.c			\
				get_token.c			\
				get_id.c			\
				utils_get_token.c	\
				errors.c

SRCS		=	$(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJS		=	$(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))
DEPS		=	./libft/libft.a

SRC_PATH	=	./src
OBJ_PATH	=	./objects

all: $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DEPS) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(DEPS) $(INCLUDE)
		echo "\033[32m[MINISHELL COMPILED]\033[0m"

LIBFT_PATH	= ./libft
./libft/libft.a: $(shell make -C $(LIBFT_PATH) -q libft.a || echo force)
	make -C $(LIBFT_PATH)

$(OBJ_PATH):
	$(MKD) -p objects

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_PATH)
	echo "\033[33mall $(NAME).o files are removed\033[0m"

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)
	echo "\033[31m$(NAME) is deleted\033[0m"

re:	fclean all

.PHONY: all clean fclean re force