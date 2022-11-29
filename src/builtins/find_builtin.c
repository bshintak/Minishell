/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 16:25:52 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_builtin(char *line, char ***env)
{
	if (!ft_strncmp(line, "pwd", 3))
		return (builtin_pwd());
	else if (!ft_strncmp(line, "echo", 5))
		return (builtin_echo(line));
	else if (!ft_strncmp(line, "cd", 2))
		return (builtin_cd(line, env));
	else if (!ft_strncmp(line, "env", 3))
		return (builtin_env(*env));
	else if (!ft_strncmp(line, "export", 6))
		return (builtin_export(line, env));
	else if (!ft_strncmp(line, "unset", 5))
		return (builtin_unset(line, env));
	// else
	// 	printf("wrong\n");
	// if (argv == "pwd")
	// 	built_pwd(argv);
}
