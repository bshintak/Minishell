/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/03 14:32:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_builtin(t_node *token, char ***env)
{
	if (!ft_strncmp(((char **)(token->data))[0], "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(((char **)(token->data))[0], "echo", 5))
		return (builtin_echo(((char **)(token->data))[0]));
	else if (!ft_strncmp(((char **)(token->data))[0], "cd", 2))
		return (builtin_cd(((char **)(token->data))[0], env));
	else if (!ft_strncmp(((char **)(token->data))[0], "env", 3))
		return (builtin_env(*env));
	else if (!ft_strncmp(((char **)(token->data))[0], "export", 6))
		return (builtin_export(((char **)(token->data))[0], env));
	else if (!ft_strncmp(((char **)(token->data))[0], "unset", 5))
		return (builtin_unset(((char **)(token->data))[0], env));
	else
		printf("is not a builtin\n");
	// if (argv == "pwd")
	// 	built_pwd(argv);
}
