/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:42:21 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/10 15:36:27 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	just_creat_her(t_node *node)
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

void	redir_in_built(t_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_INPUT_REDIR)
		{
			if (open((char *)node->data, O_RDONLY, 0644) == -1)
			{
				ft_putstr_fd("Error: couldn't open file: ", STDERR_FILENO);
				ft_putendl_fd(node->data, STDERR_FILENO);
				(*exit_status()).i = 1;
				exit((*exit_status()).i);
			}
		}
		else if (node->id == ID_INPUT_HERDOC)
			just_creat_her(node);
	}
}

int	out_help(int tmp, int status, int *out, t_node *node)
{
	int	aux;

	aux = *out;
	if (status == 1)
	{
		aux--;
		tmp = open(node->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (status == 2)
	{
		aux--;
		tmp = open(node->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	out = &aux;
	return (tmp);
}

int	redir_out_built(t_pipex *pp, t_node *node)
{
	int	fd;
	int	tmp;
	int	out;

	tmp = 0;
	out = pp->out + 1;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_OUTPUT_REDIR)
			tmp = out_help(tmp, 1, &out, node);
		else if (node->id == ID_OUTPUT_APPEND)
			tmp = out_help(tmp, 2, &out, node);
		error_redir(tmp, node);
		if (pp->out == out)
			fd = tmp;
		else
			close(fd);
	}
	return (fd);
}

int	redir_builtin(t_node *node, t_pipex *pp)
{
	num_redir(pp, node);
	if (pp->in > 0)
		redir_in_built(node);
	else if (pp->out > 0)
		return (redir_out_built(pp, node));
	else
		return (1);
	return (0);
}
