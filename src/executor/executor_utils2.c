/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:14:20 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 16:36:45 by bshintak         ###   ########.fr       */
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
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	if (ft_strncmp(env, "PATH=", 5))
		return (NULL);
	tmp = ft_split(env, ':');
	tmp2 = ft_strjoin("/", cmd);
	tmp3 = get_cmd_path(tmp, tmp2);
	free(tmp);
	return (tmp3);
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
	free(pwd);
	return (NULL);
}
