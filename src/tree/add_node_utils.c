/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:56:39 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/08 12:10:02 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_on_top(t_node **tree, t_node *node)
{
	t_node	*top;

	top = *tree;
	if (!top)
		top = node;
	else
	{
		node->left = top;
		top->up = node;
		top = node;
	}
	*tree = top;
}

void	add_on_right(t_node *node, t_node *new)
{
	if (!node || !new)
		return ;
	if (node->right)
	{
		new->left = node->right;
		node->right->up = new;
	}
	node->right = new;
	new->up = node;
}

void	add_on_left(t_node *node, t_node *new)
{
	if (!node || !new)
		return ;
	if (node->left)
	{
		new->left = node->left;
		node->left->up = new;
	}
	node->left = new;
	new->up = node;
}
