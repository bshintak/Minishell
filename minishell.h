/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:23:53 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/26 18:20:13 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

# define SPACES		" \t\f\n\v\r"
# define OPERATORS	"<>|"
# define ID_WORD	0
# define ID_OPER	1

typedef struct	s_token
{
	char	*content;
	char	*word;
	int		id;
	int		start;
}				t_token;

typedef struct	s_type
{
	char	**command;
	char	*word;
	char 	*redirection;
	char	*pipe;
}				t_type;

/*		LIBFT		*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char *s, unsigned int start, int len);
char	*ft_strrchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int		ft_strlen(char *str);
int		is_space(char c);

/*		SRC		*/

char	*get_token(char *line);
void	read_line(char **argv);
void	exec_line(char *line);
void	find_builtin(char *line);
void	builtin_pwd(void);
void	builtin_cd(void);
void	builtin_echo(char *line);
void	all_ctrl(void);

#endif