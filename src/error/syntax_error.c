/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:52:51 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/29 16:25:54 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_node(t_node *node)
{
	while (node)
	{
		if (!(node->data))
			return (1);
		node = node->left;
	}
	return (0);
}

int	error_tree(t_node *tree, char *token)
{
	t_node	*aux;

	aux = NULL;
	if (!token && is_pipe(tree) && !tree->right)
	{
		print_error(token);
		return (1);
	}
	if (is_pipe(tree))
		aux = tree->right;
	else
		aux = tree;
	if (error_node(aux))
	{
		ft_putendl_fd("if error_node", 1);
		print_error(token);
		return (1);
	}
	return (0);
}

static int	is_syntax_error(t_node *tree, char *token)
{
	int	status;

	status = 0;
	if (!token || get_id(token) != ID_WORD)
		status = error_tree(tree, token);
	return (status);
}

int	syntax_error(t_node *tree, char *token)
{
	if (is_syntax_error(tree, token))
	{
		tree_free(tree);
		if (token)
			free (token);
		return (1);
	}
	return (0);
}

// int	error_pipe(char *token)
// {
// 	if (token && get_id(token) == ID_PIPE)
// 	{
// 		print_error(token);
// 		return (1);
// 	}
// 	return (0);
// }

// int	syntax_error(t_node *tree, char *token)
// {
// 	int	status;

// 	status = 0;
// 	if (!tree && get_id(token) == ID_PIPE)
// 		status = error_pipe(token);
// 	if (tree)
// 		status = error_tree(tree, token);
// 	return (status);
// }
