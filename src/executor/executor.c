/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:36 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/08 12:11:15 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_cmd(t_node *tree, char ***env)
{
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	cmd = ((char **)(tree->data));
	if (access(cmd[0], F_OK) == 0)
		execve(cmd[0], cmd, *env);
	else
	{
		paths = get_paths(*env);
		if (!paths)
			return ;
		cmd_path = get_cmd_path(cmd[0], paths);
		if (!cmd_path)
			return ;
		execve(cmd_path, cmd, *env);
	}
}

void	executor(t_node **tree, char ***env)
{
	t_node	*node;

	node = *tree;
	if (!node->right)
	{
		if (node->id == ID_BUILTIN)
			find_builtin(node, env);
		if (node->id == ID_COMMAND)
			execute_cmd(node, env);
	}
	else
	{	
		while (node->right->id == ID_PIPE)
		{
			if (node->left->id == ID_BUILTIN)
				find_builtin(node->left, env);
			if (node->left->id == ID_COMMAND)
				execute_cmd(node->left, env);
			node = node->right;
		}
		if (node->left->id == ID_BUILTIN)
			find_builtin(node->left, env);
		else if (node->left->id == ID_COMMAND)
			execute_cmd(node->left, env);
		if (node->right->id == ID_BUILTIN)
			find_builtin(node->right, env);
		else if (node->right->id == ID_COMMAND)
			execute_cmd(node->right, env);
	}
}
