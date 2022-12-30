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

void	redir_in(t_pipex *pp, t_node *node)
{
	int	in;
	int	fd;

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
		}
	}
}

void	redir_out(t_pipex *pp, t_node *node)
{
	int	out;
	int	fd;

	out = pp->out + 1;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_OUTPUT_REDIR)
		{
			fd = open(node->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			out--;
		}
		else if (node->id == ID_OUTPUT_APPEND)
		{
			fd = open(node->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
			out--;
		}
		error_redir(fd, node);
		if (out == pp->out)
			dup2(fd, STDOUT_FILENO);
		else
			close(fd);
	}
}

void	redir(t_pipex *pp, t_node *node)
{
	num_redir(pp, node);
	if (pp->in)
		redir_in(pp, node);
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
