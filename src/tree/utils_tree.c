/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:08:08 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/30 16:36:41 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *token)
{
	if (!ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "exit"))
		return (ID_BUILTIN);
	return (ID_COMMAND);
}

int	strlen_matrix(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
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
		fail_malloc(new_str);
		new_str[0] = ft_strdup(token);
		new_str[1] = NULL;
	}
	else
	{
		size = strlen_matrix(str);
		new_str = malloc(sizeof(char *) * (size + 2));
		fail_malloc(new_str);
		while (str[++i])
			new_str[i] = str[i];
		new_str[i] = ft_strdup(token);
		new_str[i + 1] = NULL;
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
