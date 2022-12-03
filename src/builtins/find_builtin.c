/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/03 15:23:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_builtin(t_node *token, char ***env)
{
	char	**cmd;

	cmd = ((char **)(token->data));
	if (!ft_strncmp(cmd[0], "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(cmd[0], "echo", 5))
		return (builtin_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (builtin_cd(cmd[0], env));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (builtin_env(*env));
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (builtin_export(cmd[0], env));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (builtin_unset(cmd[0], env));
	else
		printf("is not a builtin\n");
	// if (argv == "pwd")
	// 	built_pwd(argv);
}
