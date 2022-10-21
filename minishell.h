/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:23:53 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/21 15:57:05 by bshintak         ###   ########.fr       */
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

typedef struct	s_built
{
	char	**command;
	char	*echo;
	char	*cd;
	char	*pwd;
	char	*export;
	char	*unset;
	char	*env;
	char	*exit;
}				t_built;

/*		LIBFT		*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		is_space(char c);

/*		SRC		*/

void	read_line(char **argv);
void	exec_line(char *line);
void	find_builtin(char *line);
void	builtin_pwd(void);
void	builtin_cd(void);
void	builtin_echo(char *line);
void	all_ctrl(void);

#endif