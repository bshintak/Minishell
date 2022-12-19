/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:50 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/19 18:05:09 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			free_strs(NULL, paths);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_strs(cmd_path, NULL);
		i++;
	}
	return (NULL);
}

static char	**put_bars(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

static	char	*get_env_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i] != NULL && env[i][0] != '\0')
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path);
}

char	**get_paths(char **env)
{
	char	*env_path;
	char	**paths;

	env_path = get_env_path(env);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free_strs(env_path, NULL);
	if (!paths)
		return (NULL);
	paths = put_bars(paths);
	if (!paths)
		return (NULL);
	return (paths);
}
