/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:22:21 by lleiria-          #+#    #+#             */
/*   Updated: 2022/11/29 16:27:47 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_var(char *var, char ***env)
{
	int		i;
	char	**copy_env;

	i = 0;
	while ((*env)[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, ft_strlen(var)) != 0)
		{
			copy_env[i] = (*env)[i];
			i++;
		}
		else
			i++;
	}
	copy_env[i] = NULL;
	free(*env);
	(*env) = copy_env;
}

int	exist_var(char *var, char **env)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, var_len) && var[var_len] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	only_unset(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 't' && line[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_unset(char *line, char ***env)
{
	if (!only_unset(line))
	{
		while (*line != ' ')
			line++;
		line++;
		printf("line: %s\n", line);
		if (exist_var(line, *env))
			delete_var(line, env);
		else
			printf("unset: `%s': not a valid identifier\n", line);
	}
}
