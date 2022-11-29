/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:12:23 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_builtin(char *line, char ***env)
{
	if (!ft_strcmp(line, "pwd"))
		return (builtin_pwd());
	else if (!ft_strncmp(line, "echo", 4))
		return (builtin_echo(line));
	else if (ft_strncmp(line, "cd", 2) == 0)
		return (builtin_cd(line, env));
	else if (ft_strncmp(line, "pwd", 3) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(line, "env", 3) == 0)
		return (builtin_env(*env));
	else if (ft_strncmp(line, "export", 6) == 0)
		return (builtin_export(line, env));
	// else
	// 	printf("wrong\n");
	// if (argv == "pwd")
	// 	built_pwd(argv);
}
