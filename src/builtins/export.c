/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:25:35 by lleiria-          #+#    #+#             */
/*   Updated: 2023/01/11 14:32:20 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	insert_var(char ***env, char *var)
{
	int		i;
	char	**copy_env;

	i = 0;
	while ((*env)[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
	{
		copy_env[i] = (*env)[i];
		i++;
	}
	copy_env[i] = ft_strdup(var);
	copy_env[i + 1] = NULL;
	free(*env);
	(*env) = copy_env;
}

int	valid_var(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_line(char *env_line, int fd)
{
	int		i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env_line[i] != '\0' && env_line[i] != '=')
	{
		ft_putchar_fd(env_line[i], fd);
		i++;
	}
	if (env_line[i] == '=')
	{
		ft_putchar_fd(env_line[i], fd);
		ft_putchar_fd('\"', fd);
		i++;
		while (env_line[i] != '\0')
		{
			ft_putchar_fd(env_line[i], fd);
			i++;
		}
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	builtin_export(char **line, char ***env, int fd)
{
	int	i;

	i = 0;
	if (!line[1])
	{
		while ((*env)[i])
		{
			print_export_line((*env)[i], fd);
			i++;
		}
	}
	else
	{
		if (valid_var(line[1]))
			insert_var(env, line[1]);
		else
		{
			ft_putstr_fd("export: \'", fd);
			ft_putstr_fd(line[1], fd);
			ft_putstr_fd("\': not a valid identifier\n", fd);
		}
	}
}
