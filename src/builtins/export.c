/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:25:35 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/06 15:40:21 by bshintak         ###   ########.fr       */
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
	copy_env[i] = var;
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
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_line(char *env_line)
{
	int		i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env_line[i] != '\0' && env_line[i] != '=')
	{
		write(1, &env_line[i], 1);
		i++;
	}
	if (env_line[i] == '=')
	{
		write(1, &env_line[i], 1);
		write(1, "\"", 1);
		i++;
		while (env_line[i] != '\0')
		{
			write(1, &env_line[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	builtin_export(char **line, char ***env)
{
	int		i;

	i = 0;
	if (!line[1])
	{
		while ((*env)[i])
		{
			print_export_line((*env)[i]);
			i++;
		}
	}
	else
	{
		if (valid_var(line[1]))
			insert_var(env, line[1]);
		else
			printf("not valid var\n");
	}
}
