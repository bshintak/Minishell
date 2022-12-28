/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:36 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/28 21:19:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	tmp = NULL;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (is_path(cmd, tmp))
		{
			j = -1;
			while (path[++j])
				free (path[j]);
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	j = -1;
	while (path[++j])
		free (path[j]);
	free(cmd);
	return (NULL);
}

char	*get_path(char *env, char *cmd)
{
	char	**tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (ft_strncmp(env, "PATH=", 5))
		return (NULL);
	tmp = ft_split(env, ':');
	tmp2 = ft_strjoin("/", cmd);
	return (get_cmd_path(tmp, tmp2));
}

int	is_path(char *str, char *path)
{
	struct stat	buf;

	lstat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" is a directory", 2);
		(*exit_status()).i = 126;
		exit((*exit_status()).i);
	}
	if (access(path, X_OK) >= 0)
		return (1);
	return (0);
}

char	*path_cmd(char *cmd, char ***env)
{
	char	*pwd;
	char	*tmp;
	char	**tmp_env;
	int		i;

	tmp_env = *env;
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
	i = -1;
	while (tmp_env[++i])
	{
		pwd = get_path(tmp_env[i], cmd);
		if (is_path(cmd, pwd))
			return (pwd);
		free(pwd);
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
	return (NULL);
}

void	process(t_node *node, t_pipex *pp, char ***env)
{
	char	**cmd;
	char	**env2;
	char	*path;

	cmd = (char **)node->data;
	env2 = *env;
	path = path_cmd(cmd[0], env);
	close(node->p[0]);
	redir(pp, node);
	rl_clear_history();
	if (node->id == ID_BUILTIN)
	{
		find_builtin(node, env);
		exit ((*exit_status()).i);
	}
	if (path)
		execve(path, node->data, env2);
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
	if (pp->num_pipe != 1)
	{
		if (pp->fd > 0)
			close (pp->fd);
		close (node->p[1]);
		pp->fd = node->p[0];
	}
	else
	{
		close (node->p[0]);
		close (node->p[1]);
		if (pp->fd > 0)
			close (pp->fd);
	}
}

void	wait_cmd(int pid, int num, char ***env)
{
	int	status;
	int	n_cmd;

	(void)env;
	n_cmd = num;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*exit_status()).i = WEXITSTATUS(status);
	while (n_cmd--)
		wait(NULL);
}

void	one_or_two_cmds(t_node *node, t_pipex *pp, char ***env)
{
	if (node->id == ID_PIPE)
	{
		do_command(node->left, env, pp);
		pp->num_pipe--;
		do_command(node->right, env, pp);
		pp->num_pipe--;
	}
	else
		do_command(node, env, pp);
}

void	mult_pipes(t_node *node, t_pipex *pp, char ***env)
{
	while(node->up)
	{
		node = node->up;
		do_command(node->right, env, pp);
		pp->num_pipe--;
	}
}

void	executor(t_node **tree, char ***env, int num)
{
	t_pipex	pp;
	t_node	*node;

	node = *tree;
	pp.num_pipe = num + 1;
	pp.num_cmd = num + 1;
	pp.fd = 0;
	while (node->left && node->left->id == ID_PIPE)
		node = node->left;
 	if (!node->up && node->id == ID_BUILTIN)
		find_builtin(node, env);
	else
	{
		one_or_two_cmds(node, &pp, env);
		mult_pipes(node, &pp, env);
	}
	wait_cmd(pp.pid, num, env);
}
