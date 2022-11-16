/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/16 10:17:56 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_builtin(char *line)
{
	if (!ft_strcmp(line, "pwd"))
		return (builtin_pwd());
	else if (!ft_strncmp(line, "echo", 4))
		return (builtin_echo(line));
	else if (ft_strncmp(line, "cd", 2) == 0)
		return (builtin_cd(line));
	else if (ft_strncmp(line, "pwd", 2) == 0)
		return (builtin_pwd());
	// else
	// 	printf("wrong\n");
	// if (argv == "pwd")
	// 	built_pwd(argv);
}
