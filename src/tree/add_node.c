/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:54:06 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/29 15:48:57 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_command(t_node **tree, t_node *node)
{
	t_node	*first_wtv;

	first_wtv = *tree;
	if (!first_wtv || is_redir(first_wtv))
		add_on_top(tree, node);
	else if (is_pipe(first_wtv))
		add_on_right(first_wtv, node);
}

void	add_redir(t_node **tree, t_node *node)
{
	t_node	*first_wtv;
	t_node	*next_wtv;

	if (!tree)
		return ;
	first_wtv = *tree;
	if (!first_wtv)
		add_on_top(tree, node);
	else if (is_command(first_wtv) || is_redir(first_wtv))
		add_on_left(first_wtv, node);
	else if (is_pipe(first_wtv))
	{
		next_wtv = first_wtv->right;
		if (!next_wtv || is_redir(next_wtv))
			add_on_right(first_wtv, node);
		else
			add_on_left(next_wtv, node);
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
