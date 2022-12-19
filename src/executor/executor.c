/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:36 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/19 18:26:12 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	absolute_path(char *cmd)
{
	(void)cmd;
	printf("aqui\n");
}

void	execute_cmd(t_node *tree, char ***env, t_pipex *pp)
{
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	cmd = ((char **)(tree->data));
	if (pipe(tree->p) == -1)
		ft_putendl_fd("Error: Pipe failed", 2);
	pp->pid = fork();
	if (pp->pid < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (pp->pid == 0)
	{
		// if (cmd[0][0] == '/')
		// 	absolute_path(cmd[0]);
		// else
		// {
			close(tree->p[0]);
			paths = get_paths(*env);
			if (!paths)
				return ;
			cmd_path = get_cmd_path(cmd[0], paths);
			if (!cmd_path)
				return ;
			execve(cmd_path, cmd, *env);
		// }
	}
	// if (access(cmd[0], F_OK) == 0)
	// 	execve(cmd[0], cmd, *env);
}

void	wait_for_cmd(int pid, int num, char **env)
{
	int		status;

	(void)num;
	(void)env;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*exit_status()).i = WEXITSTATUS(status);
}

void	one_or_two_cmds(t_node *node, char ***env, t_pipex pp)
{
	if (node->id == ID_PIPE)
	{
		if (node->left->id == ID_BUILTIN)
			find_builtin(node->left, env);
		else if (node->left->id == ID_COMMAND)
			execute_cmd(node->left, env, &pp);
		if (node->right->id == ID_BUILTIN)
			find_builtin(node->right, env);
		else if (node->right->id == ID_COMMAND)
			execute_cmd(node->right, env, &pp);
	}
	else
	{
		if (node->id == ID_BUILTIN)
			find_builtin(node, env);
		else if (node->id == ID_COMMAND)
			execute_cmd(node, env, &pp);
	}
}

void	executor(t_node **tree, char ***env, int num)
{
	t_node	*node;
	t_pipex	pp;

	node = *tree;
	(void)num;
	// pp->num_pipe = num;
	// pp->fd = 0;
	one_or_two_cmds(node, env, pp);
	while (node->up)
	{
		printf("aqui\n");
		node = node->up;
		if (node->right->id == ID_BUILTIN)
		{
			find_builtin(node->right, env);
			pp.num_pipe--;
		}
		else if (node->right->id == ID_COMMAND)
		{
			execute_cmd(node, env, &pp);
			pp.num_pipe--;
		}
	}
	// wait_for_cmd(pp.pid, num, *env);
	// wait_for_cmd(pp->pid, num, *env);
	
}
