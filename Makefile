# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 17:10:37 by bshintak          #+#    #+#              #
#    Updated: 2023/01/03 12:19:48 by lleiria-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address
INCLUDE		=	-lreadline
MKD			=	mkdir
RM			=	rm -f

BUILTINS	= 	builtins/pwd.c					\
				builtins/find_builtin.c			\
				builtins/echo.c					\
				builtins/cd.c					\
				builtins/env.c					\
				builtins/export.c				\
				builtins/unset.c				\
				builtins/exit.c

TOKEN		=	token/get_token.c				\
				token/get_id.c					\
				token/word_parser.c				\
				token/utils_word_parser.c		\
				token/utils_get_token.c			\
				token/update_dollar_quote.c		\
				token/utils_update_dol_quo.c

TREE		=	tree/create_tree.c				\
				tree/add_node.c					\
				tree/add_node_utils.c			\
				tree/is_node.c					\
				tree/put_something.c			\
				tree/utils_tree.c				\
				tree/fail.c						\
				tree/tree_free.c

EXECUTOR	=	executor/executor.c				\
				executor/executor_utils.c		\
				executor/pipes.c				\
				executor/wait.c

REDIR		=	redirections/redirection.c		\

EXPAND		=	expand/expand_home.c			\
				expand/expand_shlvl.c			\
				expand/expand_dollar.c			\
				expand/expand_exit.c

ERROR		=	error/syntax_error.c			\
				error/errors.c

SRC_WTV		=	main.c							\
				parser.c						\
				get_env.c						\
				utils_exit.c					\
				ctrl.c							\
				print_tree.c

SRC_NAME	=	$(BUILTINS) $(TOKEN) $(TREE) $(EXECUTOR) $(REDIR) $(EXPAND) $(ERROR) $(SRC_WTV)

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