/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:11:34 by bshintak         ###   ########.fr       */
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

void	builtin_cd(char *line, char ***env)
{
	char	*new_path;
	char	*old_path;
	int		i;

	while (*line != ' ')
		line++;
	line++;
	printf ("line: %s\n", line);
	old_path = getcwd(NULL, 1025);
	printf("old path: %s\n", old_path);
	if (chdir(line) == -1)
		printf("error\n");
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
