/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:23:53 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/28 18:13:08 by bshintak         ###   ########.fr       */
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

# define SPACES				" \t\f\n\v\r"
# define OPERATORS			"<>|"
# define SPACES_OPERATORS	" \t\f\n\v\r<>|"
# define ID_WORD	0
# define ID_REDIR	1
# define ID_PIPE	2

// typedef enum e_type
// {
// 	ID_WORD,
// 	ID_PIPE,
// 	ID_REDIR,
// } t_token_type;

typedef struct	s_token
{
	char			*content;
	int				start;
	// t_token_type	id;
	int				id;
}				t_token;

// typedef struct	s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }				t_list;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

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

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);

/*		SRC		*/

void	parser(char *line);
void	token_list(char *line, t_list **idk);
char	*get_token1(char *line);
void	read_line(char **argv);
void	exec_line(char *line);
void	find_builtin(char *line);
void	builtin_pwd(void);
void	builtin_cd(void);
void	builtin_echo(char *line);
void	all_ctrl(void);

#endif