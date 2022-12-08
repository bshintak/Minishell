# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 16:27:20 by bshintak          #+#    #+#              #
#    Updated: 2022/12/08 11:20:47 by lleiria-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME =	libft.a
SRC =	ft_strcmp			\
		ft_strncmp			\
		ft_strchr			\
		ft_strrchr			\
		ft_strdup			\
		ft_strlen			\
		ft_strjoin			\
		ft_substr			\
		is_space			\
		ft_memcpy			\
		ft_putstr_fd		\
		ft_putchar_fd		\
		ft_putendl_fd		\
		ft_itoa				\
		ft_atoi				\
		ft_isalnum			\
		ft_isdigit			\
		ft_split			\
		ft_strnstr			\

CC =		gcc
RM =		rm -f
CFLAGS =	-Wall -Werror -Wextra -I.

all:$(NAME)

$(NAME): $(SRC:=.o)
			ar rc $(NAME) $(SRC:=.o)
clean:
	$(RM)	$(SRC:=.o)
fclean: clean
		$(RM)	$(NAME)
re:	fclean	$(NAME)
bonus:	$(SRC:=.o)
		ar rc $(NAME) $(SRC:=.o)