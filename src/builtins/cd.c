/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/23 12:46:10 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_old(char ***env, char *old_path)
{
	int		i;
	char	**copy_env;

	i = -1;
	while ((*env)[++i])
		if (!ft_strncmp((*env)[i], "OLDPWD=", 7))
			return ;
	copy_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while ((*env)[++i])
		copy_env[i] = (*env)[i];
	copy_env[i] = ft_strjoin("OLDPWD=", old_path);
	copy_env[i + 1] = NULL;
	free(old_path);
	free(*env);
	(*env) = copy_env;
}

void	update_env(char *old_path, char *new_path, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "OLDPWD=", 7) == 0)
		{
			if ((*env)[i])
				free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", old_path);
		}
		if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
		{
			if ((*env)[i])
				free((*env)[i]);
			(*env)[i] = ft_strjoin("PWD=", new_path);
			if (new_path)
				free(new_path);
		}
		i++;
	}
}

void	error_cd(char *token)
{
	ft_putstr_fd("cd: ", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putchar_fd('\n', 1);
}

void	builtin_cd(char **line, char ***env)
{
	char	*new_path;
	char	*old_path;
	int		i;

	old_path = getcwd(NULL, 1025);
	printf("old path: %s\n", old_path);
	if (chdir(line[1]) == -1)
	{
		error_cd(line[1]);
		return ;
	}
	new_path = getcwd(NULL, 1025);
	printf("new path: %s\n", new_path);
	update_env(old_path, new_path, env);
	create_old(env, old_path);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "OLDPWD=", 7) == 0
			|| ft_strncmp((*env)[i], "PWD=", 4) == 0)
			printf("env[%d]: %s\n", i, (*env)[i]);
		i++;
	}
}
