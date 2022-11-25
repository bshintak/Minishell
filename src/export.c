/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:25:35 by lleiria-          #+#    #+#             */
/*   Updated: 2022/11/25 16:16:29 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int valid_var(char *var)
// {
// 	int i;

// 	i = 0;
// 	if (ft_isdigit(var[i]))
// 		return (0);
// 	while (var[i])
// 	{
// 		if (!ft_isalnum(var[i]) && var[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void	print_export_line(char *env_line)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env_line[i] != '=')
	{
		write(1, &env_line[i], 1);
		i++;
	}
	write(1, &env_line[i], 1);
	write(1, "\"", 1);
	i++;
	while (env_line[i] != '\0')
	{
		write(1, &env_line[i], 1);
		i++;
	}
	ft_putstr_fd("\"\n", 1);
}

int	only_export(char *line)
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

void	builtin_export(char *line, char ***env)
{
	int		i;

	i = 0;
	if (only_export(line))
	{
		while ((*env)[i])
		{
			print_export_line((*env)[i]);
			i++;
		}
	}
	while (*line != ' ')
		line++;
	line++;
	printf("line: %s\n", line);
	// if (valid_var(line))
}