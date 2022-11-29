/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:27:59 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/28 14:34:41 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_free(char **node)
{
	int	i;

	i = -1;
	while (node[++i])
		free(node[i]);
	free (node);
}

void	node_free(t_node *node)
{
	if (is_redir(node))
	{
		if (node->data)
			free(node->data);
	}
	else if (is_command(node))
	{
		if (node->data)
			node_free(node);
	}
	free(node);
}

void	tree_free(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		node_free(tree->left);
	else if (tree->right)
		node_free(tree->right);
}