/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:22:21 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/26 17:01:59 by bshintak         ###   ########.fr       */
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
