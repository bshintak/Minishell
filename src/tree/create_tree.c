/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:43:06 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/03 14:54:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_node	*create_node(int id, int builtin)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		ret_error("ERROR: Memory allocation failed.\n");
	if (builtin == 1)
		id = ID_BUILTIN;
	node->id = id;
	printf("node id = %d\n", node->id);
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
	if (is_herdoc(node))
		put_herdoc(node, token);
	else if (is_redir(node))
		put_redir(node, token);
	else if (is_command(node))
		put_command(node, token);
	return (node);
}

void	add_new_node(t_node **tree, t_node *node)
{
	if (is_command(node))
		add_command(tree, node);
	else if (is_redir(node))
		add_redir(tree, node);
	else if (is_pipe(node))
		add_pipe(tree, node);
}

void	create_tree(t_node **tree, char *token, int id)
{
	t_node	*new_node;
	t_node	*node_with_type;
	t_node	*node;
	int		builtin;

	builtin = 0;
	new_node = NULL;
	node_with_type = NULL;
	if (id == ID_WORD)
	{
		node = search_node(*tree);
		if (node)
			check_node_type(node, token);
		else
		{
			if (is_builtin(token))
				builtin = 1;
			new_node = create_node(ID_COMMAND, builtin);
			node_with_type = check_node_type(new_node, token);
			add_new_node(tree, node_with_type);
		}
	}
	else
		add_new_node(tree, create_node(id, builtin));
}
