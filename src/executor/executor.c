/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:36 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/22 15:18:23 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_path(char *cmd, char *path)
{
	struct stat	buf;

	lstat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is a directory", 2);
		(*exit_status()).i = 126;
		exit((*exit_status()).i);
	}
	if (access(path, X_OK) >= 0)
		return (1);
	return (0);
}

char	*not_absolute(char *cmd, char **path)
{
	char	*pwd;
	char	*tmp;
	int		i;

	i = -1;
	if (cmd[0] && cmd[0] == '.')
	{
		pwd = getcwd(NULL, 0);
		tmp = ft_strjoin(pwd, "/");
		free(pwd);
		pwd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (is_path(cmd, pwd))
			return (pwd);
	}
	if (!path)
	{
		ft_putstr_fd("shell: path is unset\n", 2);
		(*exit_status()).i = 127;
		exit((*exit_status()).i);
	}
	while (path[++i])
	{
		pwd = ft_strjoin(path[i], cmd);
		if (is_path(cmd, pwd))
			return (pwd);
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
	return (NULL);
}

char	*cmd_path(char *cmd, char **env)
{
	//if (cmd[0] == '/')
	//	return (absolute_path(cmd, env));
	//else
	return (not_absolute(cmd, get_paths(env)));
}

void	execute_cmd(t_node *tree, char ***env, t_pipex *pp)
{
	char	**cmd;

	cmd = ((char **)(tree->data));
	if (pipe(tree->p) == -1)
		ft_putendl_fd("Error: Pipe failed", 2);
	pp->pid = fork();
	if (pp->pid < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (pp->pid == 0)
		execve(cmd_path(cmd[0], *env), tree->data, *env);
}

void	wait_for_cmd(int pid, int num, char **env)
{
	int		status;
	int		wtv;

	(void)num;
	(void)env;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*exit_status()).i = WEXITSTATUS(status);
	num--;
	while (num)
	{
		wait(&wtv);
			num--;
	}
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
	pp.num_pipe = num;
	pp.fd = 0;
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
	
}
