/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:35:18 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 17:02:03 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_echo(char **cmd, int i, char aux)
{
	if (cmd[i + 1])
	{
		while (cmd[i + 1])
		{
			ft_putstr_fd(cmd[i++], 1);
			ft_putchar_fd(' ', 1);
		}
	}
	if (aux == 'y')
		ft_putendl_fd(cmd[i], 1);
	else if (aux == 'n')
		ft_putstr_fd(cmd[i], 1);
}

void	builtin_echo(char **cmd)
{
	if (!cmd[1])
		ft_putstr_fd("\n", 1);
	else if (!ft_strncmp(cmd[1], "-n", 3) && cmd[2])
		print_echo(cmd, 2, 'n');
	else if (ft_strncmp(cmd[1], "-n", 3))
		print_echo(cmd, 1, 'y');
}
