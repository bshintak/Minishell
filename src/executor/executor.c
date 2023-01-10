/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:36 by lleiria-          #+#    #+#             */
/*   Updated: 2023/01/10 12:16:14 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process(t_node *node, t_pipex *pp, char ***env)
{
	char	**cmd;
	char	**env2;
	char	*path;

	cmd = (char **)node->data;
	env2 = *env;
	if (node->id == ID_COMMAND || node->id == ID_BUILTIN)
		path = path_cmd(cmd[0], env);
	close(node->p[0]);
	redir(pp, node, *env);
	rl_clear_history();
	if (node->id == ID_BUILTIN)
	{
		find_builtin(node, env);
		exit ((*exit_status()).i);
	}
	if (path)
		execve(path, node->data, env2);
	free (path);
	close (node->p[1]);
	close (node->p[0]);
	close (pp->fd);
}

void	do_command(t_node *node, char ***env, t_pipex *pp)
{
	if (pipe(node->p) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", STDERR_FILENO);
		(*exit_status()).i = 1;
		exit((*exit_status()).i);
	}
	pp->pid = fork();
	if (pp->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", STDERR_FILENO);
		(*exit_status()).i = 1;
		exit((*exit_status()).i);
	}
	else if (pp->pid == 0)
		process(node, pp, env);
	close_pipes(pp, node);
}

void	one_or_two_cmds(t_node *node, t_pipex *pp, char ***env)
{
	int		i = -1;
	char	**cmd;

	cmd = (char **)node->data;
	if (node->id == ID_PIPE)
	{
		do_command(node->left, env, pp);
		pp->num_pipe--;
		do_command(node->right, env, pp);
		pp->num_pipe--;
	}
	else
	{
		while (cmd[++i])
			printf("do command %s\n", cmd[i]);
		do_command(node, env, pp);
	}
}

void	mult_pipes(t_node *node, t_pipex *pp, char ***env)
{
	while (node->up)
	{
		node = node->up;
		do_command(node->right, env, pp);
		pp->num_pipe--;
	}
}

void	executor(t_node **tree, char ***env, int num, t_heredoc *wtv)
{
	t_pipex	pp;
	t_node	*node;

	node = *tree;
	pp.num_pipe = num + 1;
	pp.num_cmd = num + 1;
	pp.fd = 0;
	while (node->left && node->left->id == ID_PIPE)
		node = node->left;
	if (tree_heredoc(&node, &pp, *env, wtv))
		return ;
	if (!node->up && node->id == ID_BUILTIN)
		find_builtin(node, env);
	else
	{
		one_or_two_cmds(node, &pp, env);
		mult_pipes(node, &pp, env);
	}
	wait_cmd(pp.pid, num);
}
