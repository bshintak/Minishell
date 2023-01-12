/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:22:21 by lleiria-          #+#    #+#             */
/*   Updated: 2023/01/12 16:20:33 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	var_len(char *var)
{
	int	len;

	len = 0;
	while (var[len] != '=' && var[len] != '\0')
		len++;
	return (len);
}

void	delete_var(char *var, char ***env)
{
	int		i;
	int		j;
	char	**copy_env;

	i = 0;
	while ((*env)[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i));
	j = 0;
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], var, var_len((*env)[i])) != 0)
		{
			copy_env[j] = (*env)[i];
			j++;
		}
		else
			free((*env)[i]);
	}
	copy_env[j] = NULL;
	free(*env);
	(*env) = copy_env;
}

int	exist_var(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, var_len(env[i])))
			return (1);
		i++;
	}
	return (0);
}

void	builtin_unset(char **line, char ***env)
{
	if (line[1] && !line[2])
	{
		if (exist_var(line[1], *env))
			delete_var(line[1], env);
		else
		{
			ft_putstr_fd("unset: \'", 1);
			ft_putstr_fd(line[1], 1);
			ft_putstr_fd("\': not a valid identifier\n", 1);
		}
	}
}
