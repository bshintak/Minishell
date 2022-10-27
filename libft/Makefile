# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 16:27:20 by bshintak          #+#    #+#              #
#    Updated: 2022/10/27 16:18:05 by bshintak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME =	libft.a
SRC =	ft_strcmp			\
		ft_strncmp			\
		ft_strchr			\
		ft_strrchr			\
		ft_strlen			\
		is_space			\
		ft_substr			\
		ft_lstnew			\
		ft_lstsize			\
		ft_lstmap			\
		ft_lstlast			\
		ft_lstiter			\
		ft_lstdelone		\
		ft_lstclear			\
		ft_lstadd_back		\
		ft_lstadd_front		\

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