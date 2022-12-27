/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:23:53 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/27 14:22:22 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
	int				id;
	int				p[2];
	void			*data;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*up;
}				t_node;

typedef struct s_exit
{
	int			i;
}				t_exit;

typedef struct s_pipex
{
	int		pipe;
	int		num_pipe;
	int		num_cmd;
	int		pid;
	int		fd;
	int		in;
	int		out;
	int		heredoc;
}				t_pipex;

# define FALSE				0
# define TRUE				1

# define SPACES_OPERATORS	" \t\f\n\v\r<>|"
# define SPACES				" \t\f\n\v\r"
# define OPERATORS			"<>|"

# define ID_WORD			0	/* 'word' */
# define ID_INPUT_REDIR		1	/* '<' */
# define ID_OUTPUT_REDIR	2	/* '>' */
# define ID_PIPE			3	/* '|' */
# define ID_INPUT_HERDOC	4	/* '<<' */
# define ID_OUTPUT_APPEND	5	/* '>>' */
# define ID_COMMAND			6	/* 'ls' */
# define ID_BUILTIN			7	/* 'builtin' */

# define SI_IGN 1
# define SI_HDOC 2
# define SI_RLINE 3
# define SI_DFL 4

# define EXIT_CTRL_C		130
# define SET_EXIT			1
# define EXIT_SYNTAX		2
# define CLEAR_EXIT			3
# define GET_EXIT			4

# define MISSING_QUOTE		1
# define DOLLAR_QUOTE		2

/*		PSEUDO_GLOBAL_VAR	*/
t_exit	*exit_status(void);

/*		LIBFT				*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char *s, unsigned int start, int len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strdup(char *s);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		is_space(char c);
int		ft_isalpha(int a);
int		ft_isascii(int a);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	**ft_split(char *s, char c);

/*		GET_ID				*/
int		get_id(char *token);

/*		GET_TOKEN			*/
char	*get_token(char *line, int reset);
char	*get_operator(int *i, char *line);
char	*get_word(int *i, char *line);

/*		UTILS_GET_TOKEN		*/
int		ft_is(char c, char *set);
int		quotation_marks(char *line, char quote);

/*		PARSER				*/
t_node	*parser(char *line, char **env);

/*		BUILTIN		*/
void	find_builtin(t_node *token, char ***env);
void	builtin_pwd(void);
void	builtin_echo(char **cmd);
void	builtin_env(char **env);
void	builtin_cd(char **line, char ***env);
void	builtin_export(char **line, char ***env);
void	builtin_unset(char **line, char ***env);
void	builtin_exit(char **line);

/*		GET_ENV				*/
char	**get_env(char **env);

/*		ERRORS				*/
void	ret_error(char *str);
void	ret_without_error(char *str);
void	print_error(char *token);
void	print_error2(char *token, int status);

/*		SYNTAX_ERROR		*/
int		syntax_error(t_node *tree, char *token);

/*		CTRL				*/
void	get_signal(int signal, void (*function)());
void	ctrl_c(int signal, siginfo_t *info, void *ucontext);
void	call_sigact(char act_choice);

/*		UTILS_EXIT				*/
int		set_exit(int status, int option);

/*		WORD_PARSER				*/
char	*word_parser(char *token, char **env);

/*		EXPAND_HOME				*/
char	*get_til(char *token, char **env);

/*		EXPAND_SHLVL			*/
char	*find_shlvl(char **env);

/*		EXPAND_DOLLAR			*/
char	*expand_dollar(char *token, char **env);

/*		EXPAND_EXIT				*/
char	*get_exit(char	*dollar, int *i, char *ret);

/*		UTILS_WORD_PARSER		*/
int		size_env(char *str);
int		size_parser(char *s);
int		word_size_parser(char *word);

/*		UPDATE_DOLLAR_QUOTE		*/
char	*update_quote_dollar(char *dollar, char **env);
char	*update_dollar(char *dollar, char **env, int *i, char *ret);
char	*join_char(char *token, char c);
char	*join_tokens(char *token, char *new_token);

/*		CREATE_TREE				*/
t_node	*create_node(int id, int builtin);
void	create_tree(t_node **tree, char *token, int id);

/*		IS_NODE					*/
int		is_command(t_node *node);
int		is_pipe(t_node *node);
int		is_redir(t_node *node);
int		is_herdoc(t_node *node);

/*		PUT_SOMETHING			*/
void	put_command(t_node *node, char *token);
void	put_redir(t_node *node, char *token);
void	put_herdoc(t_node *node, char *token);

/*		UTILS_TREE				*/
char	**update_string(char **str, char *token);
t_node	*search_node(t_node *tree);
int		is_builtin(char *token);
void	fail_malloc2(void *str);

/*		ADD_NODE				*/
void	add_pipe(t_node **tree, t_node *node);
void	add_redir(t_node **tree, t_node *node);
void	add_command(t_node **tree, t_node *node);

/*		ADD_NODE_UTILS			*/
void	add_on_top(t_node **tree, t_node *node);
void	add_on_right(t_node *node, t_node *new);
void	add_on_left(t_node *node, t_node *new);

/*		TREE_FREE				*/
void	tree_free(t_node *tree);

/*		EXECUTOR				*/
void	executor(t_node **tree, char ***env, int num);
// char	**get_paths(char **env);
char	*get_cmd_path(char **path, char *cmd);
int		is_path(char *str, char *path);

/*		PRINT_TREE				*/
void	print2d(t_node *root);


#endif