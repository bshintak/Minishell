/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:43:06 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 10:26:40 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*create_node(int id)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (0);
	node->id = id;
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	node->up = NULL;
	return (node);
}

t_node	*check_node_type(t_node *node, char *token)
{
	if (!node || !token)
		return (NULL);
	else if (is_redir(node))
		put_redir(node, token);
	else if (is_command(node))
		put_command(node, token);
	return (node);
}

void	add_new_node(t_node **tree, t_node *node)
{
	if (is_redir(node))
		add_redir(tree, node);
	else if (is_command(node))
		add_command(tree, node);
	else if (is_pipe(node))
		add_pipe(tree, node);
}

void	create_tree(t_node **tree, char *token, int id)
{
	t_node	*new_node;
	t_node	*node_with_type;
	t_node	*node;

	new_node = NULL;
	node_with_type = NULL;
	if (id == ID_WORD)
	{
		node = search_node(*tree);
		if (node)
			check_node_type(node, token);
		else
		{
			id = is_builtin(token);
			new_node = create_node(id);
			node_with_type = check_node_type(new_node, token);
			add_new_node(tree, node_with_type);
		}
	}
	else
		add_new_node(tree, create_node(id));
}
