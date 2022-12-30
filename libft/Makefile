# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 16:27:20 by bshintak          #+#    #+#              #
#    Updated: 2022/12/30 15:56:35 by bshintak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME =	libft.a
SRC =	ft_strcmp			\
		ft_strncmp			\
		ft_strchr			\
		ft_strdup			\
		ft_strlen			\
		ft_strjoin			\
		ft_substr			\
		ft_memcpy			\
		ft_memset			\
		ft_putstr_fd		\
		ft_putchar_fd		\
		ft_putendl_fd		\
		ft_itoa				\
		ft_atoi				\
		ft_isalnum			\
		ft_isdigit			\
		ft_isalpha			\
		ft_isascii			\
		ft_split			\
		ft_calloc			\
		ft_bzero

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