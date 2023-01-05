/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:16:17 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 16:05:07 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_readline_her(char *str, char *eof, int exit_stat)
{
	if (!str)
	{
		ft_putstr_fd("\nshell: warning: here-document delimited ", 1);
		ft_putstr_fd("by end-of-file (wanted `", 1);
		write(1, eof, ft_strlen(eof) - 1);
		ft_putstr_fd("')\n", 1);
		free(eof);
		free(str);
		exit(exit_stat);
	}
	free (eof);
}

void	update_status(int val2)
{
	if (WIFSIGNALED(val2))
	{
		(*exit_status()).i = WTERMSIG(val2) + 128;
		if ((*exit_status()).i == 130)
			write(1, "\n", 1);
	}
	else
		(*exit_status()).i = WEXITSTATUS(val2);
}

int	wait_heredoc(t_node **tree, t_pipex *e)
{
	int	stat;

	close(((*tree)->p)[1]);
	waitpid(e->pid, &stat, 0);
	update_status(stat);
	if ((*exit_status()).i == 129 || (*exit_status()).i == 130)
	{
		if ((*exit_status()).i == 129)
			(*exit_status()).i = 0;
		return (1);
	}
	return (0);
}

void	new_readline2(int fd, t_node *node, char **env)
{
	char	*new_line;
	char	*new_node;
	char	*join;
	char	*parser;

	new_node = ft_strdup(node->data);
	while (1)
	{
		new_line = readline("> ");
		error_readline_her(new_line, ft_strjoin(node->data, "\n"), 129);
		if (new_line)
		{
			if (!ft_strncmp(new_line, new_node, ft_strlen(node->data)) 
				&& (ft_strlen(new_line) == ft_strlen(new_node)))
				break ;
			join = ft_strjoin(new_line, "\n");
			free (new_line);
			parser = word_parser(join, env, REDIR);
			write(fd, parser, ft_strlen(parser));
			free(join);
		}
	}
	rl_clear_history();
	free(new_line);
	free(new_node);
	exit (0);
}

int	process_heredoc(t_node **node, t_pipex *pp, int i, char **env)
{
	if (i == pp->in)
		new_readline2((*node)->p[1], *node, env);
	else
		new_readline2(-1, *node, env);
	return (0);
}

int	tree_heredoc(t_node	**tree, t_pipex *pp, char **env)
{
	t_node	*node;

	node = *tree;
	if (node->id == ID_COMMAND)
	{
		if (execute_heredoc(tree, pp, env))
			return (1);
	}
	if (node->id == ID_PIPE)
	{
		if (execute_heredoc(&((*tree)->left), pp, env))
			return (1);
		if (execute_heredoc(&((*tree)->right), pp, env))
			return (1);
	}
	while (node->up)
	{
		node = node->up;
		if (execute_heredoc(tree, pp, env))
			return (1);	
	}
	return (0);
}

int	ft_heredoc(t_node **tree, t_pipex *pp, char **env, int i)
{
	t_node	*node;

	node = *tree;
	if (node->id == ID_INPUT_HERDOC)
	{
		if (pipe(node->p) == -1)
		{
			ft_putstr_fd("Error: couldn't open pipe\n", STDERR_FILENO);
			(*exit_status()).i = 1;
			exit((*exit_status()).i);
		}
		pp->pid = fork();
		rl_clear_history();
		if (pp->pid < 0)
		{
			ft_putstr_fd("Error: couldn't create a new process\n", STDERR_FILENO);
			(*exit_status()).i = 1;
			exit((*exit_status()).i);
		}
		else if (pp->pid == 0)
			process_heredoc(&node, pp, i, env);
	}
	return (wait_heredoc(tree, pp));
}

int	execute_heredoc(t_node **tree, t_pipex *pp, char **env)
{
	t_node	*node;
	int		i;

	i = 0;
	node = *tree;
	num_redir(pp, node);
	while (node->left)
		node = node->left;
	while (node->id != ID_COMMAND)
	{
		if (node->id == ID_INPUT_HERDOC || node->id == ID_INPUT_REDIR)
		{
			i++;
			if (ft_heredoc(&node, pp, env, i))
				return (1);
		}
		node = node->up;
	}
	return (0);
}