# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 17:10:37 by bshintak          #+#    #+#              #
#    Updated: 2022/12/03 14:02:50 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra #-fsanitize=address
INCLUDE		=	-I ~/.brew/opt/readline/include -lreadline
MKD			=	mkdir
RM			=	rm -f

BUILTINS	= 	builtins/pwd.c				\
				builtins/find_builtin.c		\
				builtins/echo.c				\
				builtins/cd.c				\
				builtins/env.c				\
				builtins/export.c			\
				builtins/unset.c			\

TOKEN		=	token/get_token.c			\
				token/get_id.c				\
				token/get_til.c				\
				token/word_parser.c			\
				token/utils_get_token.c

TREE		=	tree/create_tree.c			\
				tree/add_node.c				\
				tree/add_node_utils.c		\
				tree/is_node.c				\
				tree/put_something.c		\
				tree/utils_tree.c			\
				tree/tree_free.c

EXECUTOR	=	executor/executor.c			\

SRC_WTV		=	main.c						\
				parser.c					\
				get_env.c					\
				utils_exit.c				\
				errors.c					\
				ctrl.c

SRC_NAME	=	$(BUILTINS) $(TOKEN) $(TREE) $(EXECUTOR) $(SRC_WTV)

SRCS		=	$(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJS		=	$(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))
DEPS		=	./libft/libft.a

SRC_PATH	=	./src
OBJ_PATH	=	./objects

all: $(NAME)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
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