/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:42:27 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/10 12:42:30 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tree_heredoc2(t_node **tree, t_pipex *pp, char **env, t_node *node)
{
	if (node->id == ID_COMMAND)
	{
		if (execute_heredoc(tree, pp, env))
			return (1);
	}
	else if (node->id == ID_PIPE)
	{
		if (execute_heredoc(&((*tree)->left), pp, env))
			return (1);
		if (execute_heredoc(&((*tree)->right), pp, env))
			return (1);
	}
	return (0);
}

int	tree_heredoc(t_node	**tree, t_pipex *pp, char **env, t_heredoc *wtv)
{
	t_node		*node;

	node = *tree;
	if (node->id == ID_COMMAND && is_heredoc(wtv))
	{
		if (exec_here_first(tree, pp, env))
			return (1);
	}
	else if (tree_heredoc2(tree, pp, env, node))
		return (1);
	while (node->up)
	{
		node = node->up;
		if (execute_heredoc(tree, pp, env))
			return (1);
	}
	return (0);
}
