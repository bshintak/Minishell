/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/06 15:52:32 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_builtin(t_node *token, char ***env)
{
	char	**cmd;

	cmd = ((char **)(token->data));
	if (!ft_strncmp(cmd[0], "pwd", 3))
		return (builtin_pwd());
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return (builtin_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return (builtin_cd(cmd, env));
	else if (!ft_strncmp(cmd[0], "env", 3))
		return (builtin_env(*env));
	else if (!ft_strncmp(cmd[0], "export", 6))
		return (builtin_export(cmd, env));
	else if (!ft_strncmp(cmd[0], "unset", 5))
		return (builtin_unset(cmd, env));
	else
		printf("is not a builtin\n");
}
