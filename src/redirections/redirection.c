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

void	redir_in(t_pipex *pp, t_node *node, char **env)
{
	int	fd;
	int	in;

	(void)env;
	in = pp->in + 1;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_INPUT_REDIR)
		{
			in--;
			fd = open((char *)node->data, O_RDONLY, 0644);
			error_redir(fd, node);
			if (in == pp->in)
				dup2(fd, STDIN_FILENO);
			else
				close(fd);
		}
		else if (node->id == ID_INPUT_HERDOC)
		{
			in--;
			if (in == pp->in)
				dup2(node->p[0], STDIN_FILENO);
		}
	}
}

void	redir_out(t_pipex *pp, t_node *node)
{
	int	fd;
	int	out;

	out = pp->out + 1;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_OUTPUT_REDIR)
		{
			out--;
			fd = open(node->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (node->id == ID_OUTPUT_APPEND)
		{
			out--;
			fd = open(node->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		error_redir(fd, node);
		if (pp->out == out)
			dup2(fd, STDOUT_FILENO);
		else
			close(fd);
	}
}

void	redir(t_pipex *pp, t_node *node, char **env)
{
	num_redir(pp, node);
	if (pp->in)
	{
		if (pp->fd)
			close(pp->fd);
		redir_in(pp, node, env);
	}
	else
		dup2(pp->fd, STDIN_FILENO);
	if (pp->out)
	{
		close(node->p[1]);
		redir_out(pp, node);
	}
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
