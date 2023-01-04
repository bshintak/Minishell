/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:39:23 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/29 11:39:23 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	num_redir(t_pipex *pp, t_node *node)
{
	pp->in = 0;
	pp->out = 0;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_INPUT_REDIR || node->id == ID_INPUT_HERDOC)
			pp->in++;
		else if (node->id == ID_OUTPUT_REDIR || node->id == ID_OUTPUT_APPEND)
			pp->out++;
	}
}

void	error_redir(int fd, t_node *node)
{
	if (fd == -1)
	{
		ft_putstr_fd("Error: couldn't open file: ", STDERR_FILENO);
		ft_putendl_fd(node->data, STDERR_FILENO);
		(*exit_status()).i = 1;
		exit((*exit_status()).i);
	}
}

void	pass_heredoc(t_node *node)
{
	char	*new_line;
	char	*new_node;

	new_node = ft_strdup(node->data);
	while (1)
	{
		new_line = readline("> ");
		if (new_line)
		{
			if (!ft_strncmp(new_line, new_node, ft_strlen(node->data))
				&& (ft_strlen(new_line) == ft_strlen(new_node)))
				break ;
		}
		else
			break ;
	}
	free(new_line);
	free(new_node);
}

void	new_readline(int fd, t_node *node, char **env)
{
	char	*new_line;
	char	*new_node;
	char	*join;
	char	*parser;

	new_node = ft_strdup(node->data);
	while (1)
	{
		new_line = readline("> ");
		if (new_line)
		{
			if (!ft_strncmp(new_line, new_node, ft_strlen(node->data)) 
				&& (ft_strlen(new_line) == ft_strlen(new_node)))
				break ;
			join = ft_strjoin(new_line, "\n");
			parser = word_parser(join, env, REDIR);
			write(fd, parser, ft_strlen(parser));
			free(join);
		}
		else
			break ;
	}
	free(new_line);
	free(new_node);
}

void	do_heredoc(t_pipex *pp, int in, t_node *node, char **env)
{
	int	fd;

	if (in != pp->in)
	{
		pass_heredoc(node);
		return ;
	}
	fd = open(".heredoccc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	error_redir(fd, node);
	new_readline(fd, node, env);
	close(fd);
	fd = open(".heredoccc", O_RDONLY, 0644);
	error_redir(fd, node);
	dup2(fd, STDIN_FILENO);
	unlink(".heredoccc");
}

void	redir_in(t_pipex *pp, t_node *node, char **env)
{
	int	fd;
	int	in;

	in = pp->in + 1;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_INPUT_REDIR)
		{
			in--;
			fd = open((char *)node->data, O_RDONLY, 0644);
			error_redir(fd, node);
			if (pp->in == 0)
				dup2(fd, STDIN_FILENO);
			else
				close(fd);
		}
		else if (node->id == ID_INPUT_HERDOC)
		{
			in--;
			do_heredoc(pp, in, node, env);
		}
	}
}

void	redir_out(t_pipex *pp, t_node *node)
{
	int	fd;

	while (node->left)
	{
		node = node->left;
		if (node->id == ID_OUTPUT_REDIR)
		{
			fd = open(node->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			pp->out--;
		}
		else if (node->id == ID_OUTPUT_APPEND)
		{
			fd = open(node->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
			pp->out--;
		}
		error_redir(fd, node);
		if (pp->out == 0)
			dup2(fd, STDOUT_FILENO);
		else
			close(fd);
	}
}

void	redir(t_pipex *pp, t_node *node, char **env)
{
	num_redir(pp, node);
	if (pp->in)
		redir_in(pp, node, env);
	else
		dup2(pp->fd, STDIN_FILENO);
	if (pp->out)
		redir_out(pp, node);
	else
	{
		if (pp->num_pipe > 1)
		{
			dup2(node->p[1], STDOUT_FILENO);
			close(node->p[1]);
		}
		else
			close(node->p[1]);
	}
}
