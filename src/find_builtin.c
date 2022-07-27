/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:43:50 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/27 11:39:00 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_builtin(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (ft_strncmp(line, "pwd", 3) == 0 && len == 3)
		return (builtin_pwd());
	else if (ft_strncmp(line, "echo", 4) == 0)
		return (builtin_echo(line));
	else
		printf("wrong\n");
	//if (argv == "pwd")
		//built_pwd(argv);
		
}
