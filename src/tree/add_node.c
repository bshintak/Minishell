/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:54:06 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 10:24:22 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_command(t_node **tree, t_node *node)
{
	t_node	*first_node;

	first_node = *tree;
	if (!first_node || is_redir(first_node))
		add_on_top(tree, node);
	else if (is_pipe(first_node))
		add_on_right(first_node, node);
}

void	add_redir(t_node **tree, t_node *node)
{
	t_node	*first_node;
	t_node	*next_node;

	if (!tree)
		return ;
	first_node = *tree;
	if (!first_node)
		add_on_top(tree, node);
	else if (is_command(first_node) || is_redir(first_node))
		add_on_left(first_node, node);
	else if (is_pipe(first_node))
	{
		next_node = first_node->right;
		if (!next_node || is_redir(next_node))
			add_on_right(first_node, node);
		else
			add_on_left(next_node, node);
	}
}

void	add_pipe(t_node **tree, t_node *node)
{
	t_node	*wtv;

	wtv = *tree;
	if (!wtv)
		wtv = node;
	else
	{
		node->left = wtv;
		wtv->up = node;
		wtv = node;
	}
	*tree = wtv;
}
