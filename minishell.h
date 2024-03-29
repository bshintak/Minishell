/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:23:53 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/12 12:53:50 by lleiria-         ###   ########.fr       */
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
# include <dirent.h>
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

typedef struct s_heredoc
{
	char	*line;
}				t_heredoc;

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
	char	*line;
}				t_pipex;

# define FALSE				0
# define TRUE				1

# define SPACES_OPERATORS	" \t\f\n\v\r<>|"
# define SPACES				" \t\f\n\v\r"
# define OPERATORS			"<>|"

# define REDIR				100

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
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
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
int		num_of_dol(char *dollar);
int		num_quotes(char *dollar);

/*		PARSER				*/
t_node	*parser(char *line, char **env);

/*		BUILTIN		*/
void	find_builtin(t_node *token, char ***env, int fd);
void	builtin_pwd(int fd);
void	builtin_echo(char **cmd, int fd);
void	builtin_env(char **env, int fd);
void	builtin_cd(char **line, char ***env);
void	builtin_export(char **line, char ***env, int fd);
void	builtin_unset(char **line, char ***env);
void	builtin_exit(char **line, char **env);
int		exist_var(char *var, char **env);
void	delete_var(char *var, char ***env);

/*		GET_ENV				*/
char	**get_env(char **env);

/*		ERRORS				*/
void	ret_error(char *str);
void	ret_without_error(char *str);
void	print_error(char *token);
void	print_error_quote(char *token, int status);
void	cmd_error(char *cmd);

/*		SYNTAX_ERROR		*/
int		syntax_error(t_node *tree, char *token);

/*		CTRL				*/
void	get_signal(int signal, void (*function)());
void	ctrl_c(int signal);

/*		UTILS_EXIT				*/
int		set_exit(int status, int option);

/*		WORD_PARSER				*/
char	*word_parser(char *token, char **env, int status);
char	*dollar_quotes(char *tk, char *dol, char **env, int *i);

/*		EXPAND_HOME				*/
char	*get_til(char *token, char **env, int status);

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
t_node	*create_node(int id);
void	create_tree(t_node **tree, char *token, int id);

/*		IS_NODE					*/
int		is_command(t_node *node);
int		is_pipe(t_node *node);
int		is_redir(t_node *node);

/*		PUT_SOMETHING			*/
void	put_command(t_node *node, char *token);
void	put_redir(t_node *node, char *token);

/*		UTILS_TREE				*/
char	**update_string(char **str, char *token);
t_node	*search_node(t_node *tree);
int		is_builtin(char *token);

/*		FAIL_MALLOC				*/
void	fail_malloc2(void *str);
void	fail_malloc(char **str);

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

/*		REDIRECTIONS			*/
void	redir(t_pipex *pp, t_node *node);
void	num_redir(t_pipex *pp, t_node *node);
int		redir_builtin(t_node *node, t_pipex *pp);
void	error_redir(int fd, t_node *node);

/*		EXECUTOR				*/
void	executor(t_node **tree, char ***env, int num, t_heredoc *wtv);
char	*get_cmd_path(char **path, char *cmd);
int		is_path(char *str, char *path);
char	*get_path(char *env, char *cmd);
char	*util_path_cmd(char *cmd, char *pwd, char *tmp);

/*		HEREDOC					*/
int		execute_heredoc(t_node **tree, t_pipex *pp, char **env);
int		exec_here_first(t_node **tree, t_pipex *pp, char **env);
int		tree_heredoc(t_node	**tree, t_pipex *pp, char **env, t_heredoc *wtv);
int		wait_heredoc(t_node **tree, t_pipex *e);
void	error_readline_her(char *str, char *eof, int exit_stat);
void	new_line_exist(char *new_line, int fd, char **env);
int		is_heredoc(t_heredoc *wtv);

/*		EXECUTOR_UTILS			*/
int		num_pipes(t_node *tree);
char	*path_cmd2(char *cmd, char ***env);
char	*path_cmd(char *cmd, char ***env);
char	*path_comander(char *cmd, char *pwd, char *tmp, char **tmp_env);

/*		CLOSE_PIPES				*/
void	close_pipes(t_pipex *pp, t_node *node);

/*		WAIT_COMMANDS				*/
void	wait_cmd(int pid, int num);

/*		PRINT_TREE				*/
void	print2d(t_node *root);

#endif