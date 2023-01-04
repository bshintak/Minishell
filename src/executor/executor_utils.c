/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:50 by lleiria-          #+#    #+#             */
/*   Updated: 2023/01/04 14:42:19 by bshintak         ###   ########.fr       */
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

	if (!path)
		return (0);
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

char	*util_path_cmd(char *cmd, char *pwd, char *tmp)
{
	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin(pwd, "/");
	free(pwd);
	pwd = ft_strjoin(tmp, cmd);
	free(tmp);
	if (is_path(cmd, pwd))
		return (pwd);
	return (NULL);
}

char	*path_cmd(char *cmd, char ***env)
{
	char	*pwd;
	char	*tmp;
	char	**tmp_env;
	int		i;

	tmp_env = *env;
	pwd = NULL;
	tmp = NULL;
	if (cmd[0] && cmd[0] == '.')
	{
		pwd = util_path_cmd(cmd, pwd, tmp);
		if (is_path(cmd, pwd))
			return (pwd);
	}
	if (pwd)
		free (pwd);
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
	(*exit_status()).i = 126;
	exit((*exit_status()).i);
	return (NULL);
}
