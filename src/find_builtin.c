/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/15 16:08:56 by lleiria-         ###   ########.fr       */
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
	// else
	// 	printf("wrong\n");
	//if (argv == "pwd")
		//built_pwd(argv);
}
