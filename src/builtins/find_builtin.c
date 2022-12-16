/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/16 17:31:09 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_builtin(t_node *token, char ***env)
{
	char	**cmd;

	cmd = ((char **)(token->data));
	if (!ft_strncmp(cmd[0], "pwd", 3))
		builtin_pwd();
	else if (!ft_strncmp(cmd[0], "echo", 4))
		builtin_echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		builtin_cd(cmd, env);
	else if (!ft_strncmp(cmd[0], "env", 3))
		builtin_env(*env);
	else if (!ft_strncmp(cmd[0], "export", 6))
		builtin_export(cmd, env);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		builtin_unset(cmd, env);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		builtin_exit(cmd);
	else
		return ;
}
