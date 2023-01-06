/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:50 by lleiria-          #+#    #+#             */
/*   Updated: 2023/01/06 16:55:37 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*path_comander(char *cmd, char *pwd, char *tmp, char **tmp_env)
{
	int		i;

	if (cmd[0] && cmd[0] == '.')
	{
		pwd = util_path_cmd(cmd, pwd, tmp);
		if (is_path(cmd, pwd))
			return (pwd);
	}
	if (pwd)
		free(pwd);
	i = -1;
	while (tmp_env[++i])
	{
		pwd = get_path(tmp_env[i], cmd);
		if (is_path(cmd, pwd))
			return (pwd);
		free(pwd);
	}
	return (NULL);
}

char	*path_cmd2(char *cmd, char ***env)
{
	char	*pwd;
	char	*tmp;
	char	**tmp_env;

	tmp_env = *env;
	pwd = NULL;
	tmp = NULL;
	pwd = path_comander(cmd, pwd, tmp, tmp_env);
	if (pwd)
		return (pwd);
	cmd_error(cmd);
	return (NULL);
}

char	*absolute_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is a directory", 2);
		(*exit_status()).i = 126;
		exit((*exit_status()).i);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		(*exit_status()).i = 127;
		exit((*exit_status()).i);
	}
	return (cmd);
}

char	*path_cmd(char *cmd, char ***env)
{
	if (cmd[0] == '/')
		return (absolute_path(cmd));
	else
		return (path_cmd2(cmd, env));
}
