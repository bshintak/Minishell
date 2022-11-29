/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:08:08 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 10:55:55 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strlen_matrix(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while(str[i])
		i++;
	}
	return (i);
}

char	**update_string(char **str, char *token)
{
	char	**new_str;
	int		size;
	int		i;
	
	i = -1;
	if (!str)
	{
		new_str = malloc(sizeof(char *) * 2);
		if (!new_str)
			ret_error("ERROR: Memory allocation failed.\n");
		new_str[0] = ft_strdup(token);
		new_str[1] = NULL;
	}
	else
	{
		size = strlen_matrix(str);
		new_str = malloc(sizeof(char *) * size + 2);
		while(str[++i])
			new_str[i] = str[i];
		new_str[i] = ft_strdup(token);
		new_str[i + 1] = 0;
		free (str);
	}
	return (new_str);
}

t_node	*search_node(t_node *tree)
{
	t_node	*node;
	t_node	*next;

	if (!tree)
		return (NULL);
	if (is_pipe(tree))
		node = tree->right;
	else
		node = tree;
	if (!node)
		return (NULL);
	next = node->left;
	if (is_redir(node) && !(node->data))
		return (node);
	else if (next && is_redir(next) && !(next->data))
		return (next);
	else if (is_command(node))
		return (node);
	return (NULL);
}
