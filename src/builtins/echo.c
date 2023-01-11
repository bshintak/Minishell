/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:35:18 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/11 15:21:15 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_echo(char **cmd, int i, char aux, int fd)
{
	if (cmd[i + 1])
	{
		while (cmd[i + 1])
		{
			ft_putstr_fd(cmd[i++], fd);
			ft_putchar_fd(' ', fd);
		}
	}
	if (aux == 'y')
		ft_putendl_fd(cmd[i], fd);
	else if (aux == 'n')
		ft_putstr_fd(cmd[i], fd);
}

void	builtin_echo(char **cmd, int fd)
{
	char	*aux;
	int		i;

	i = 0;
	(*exit_status()).i = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	aux = cmd[1];
	while (aux[++i])
	{
		if (aux[i] != 'n')
		{
			print_echo(cmd, 1, 'y', fd);
			return ;
		}
	}
	if (!ft_strncmp(cmd[1], "-n", 2) && cmd[2])
		print_echo(cmd, 2, 'n', fd);
	else if (ft_strncmp(cmd[1], "-n", 2))
		print_echo(cmd, 1, 'y', fd);
}
