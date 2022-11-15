/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:23:53 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/15 16:42:48 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*up;
}				t_node;

# define FALSE				0
# define TRUE				1

# define SPACES_OPERATORS	" \t\f\n\v\r<>|"
# define SPACES				" \t\f\n\v\r"
# define OPERATORS			"<>|"

# define ID_WORD			0	/* 'wtv' */
# define ID_INPUT_REDIR		1	/* '<' */
# define ID_OUTPUT_REDIR	2	/* '>' */
# define ID_PIPE			3	/* '|' */
# define ID_INPUT_HERDOC	4	/* '<<' */
# define ID_OUTPUT_APPEND	5	/* '>>' */

# define EXIT_CTRL_C		130
# define SET_EXIT			1
# define CLEAR_EXIT			2

/*		LIBFT		*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char *s, unsigned int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);

void	*ft_memcpy(void *dest, const void *src, size_t n);
int		is_space(char c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

/*		GET_ID		*/
int		get_id(char *token);

/*		GET_TOKEN	*/
char	*get_token(char *line, int reset);
char	*get_operator(int *i, char *line);
char	*get_word(int *i, char *line);

/*		UTILS GET_TOKEN		*/
int		ft_is(char c, char *set);
char	*find_string(char *find, char **str);
int		quotation_marks(int *i, char *line);

/*		PARSER		*/
void	parser(char *line, t_node *tree, char **env);

/*		BUILTIN		*/
void	find_builtin(char *line);
void	builtin_pwd(void);
void	builtin_echo(char *line);
void	builtin_env(void);
void	builtin_cd(char *line);

/*		GET_ENV		*/
char	**get_env(char **env);

/*		GET_TIL		*/
char	*get_til(char *token, char **env);

/*		ERRORS		*/
char	*ret_error(char *str);

/*		CTRL		*/
void	get_signal(int signal, void (*function)());
void	ctrl_c(int signal);
void	ctrl_slash(void);

/*		UTILS_EXIT		*/
int		set_exit(int status, int option);

#endif