/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:20:40 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/30 16:28:20 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes(t_pipex *pp, t_node *node)
{
	if (pp->num_pipe != 1)
	{
		if (pp->fd > 0)
			close (pp->fd);
		close (node->p[1]);
		pp->fd = node->p[0];
	}
	else
	{
		close (node->p[0]);
		close (node->p[1]);
		if (pp->fd > 0)
			close (pp->fd);
	}
}

int	num_pipes(t_node *tree)
{
	t_node	*node;
	int		num;

	num = 0;
	node = tree;
	if (node->left && !is_redir(node->left))
	{
		num++;
		while (node->left->id == ID_PIPE)
		{
			num++;
			node = node->left;
		}
	}
	return (num);
}
