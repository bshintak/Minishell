/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:52:44 by lleiria-          #+#    #+#             */
/*   Updated: 2023/01/10 12:01:22 by lleiria-         ###   ########.fr       */
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
