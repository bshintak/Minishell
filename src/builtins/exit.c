/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:03:28 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/11 15:43:55 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	num_exit(int num)
{
	if (num >= 0 && num <= 255)
		return (num);
	else
		return (num % 256);
}

int	type_exit(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_isascii(line[i]) && !ft_isdigit(line[i]))
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(line, 2);
			ft_putendl_fd(" : numeric argument required", 2);
			return (2);
		}
	}
	i = 0;
	if (ft_isdigit(line[i]))
	{
		ft_putstr_fd("exit\n", 1);
		return (num_exit(ft_atoi(line)));
	}
	return (0);
}

void	builtin_exit(char **line, char **env)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	if (!line[1])
	{
		ft_putstr_fd("exit\n", 1);
		status = 0;
	}
	else if (line[1] && line[2])
	{
		(*exit_status()).i = 1;
		ft_putstr_fd("exit: too many arguments\n", 1);
		while (env[++i])
			free (env[i]);
		free (env);
		return ;
	}
	else
		status = type_exit(line[1]);
	while (env[++i])
		free (env[i]);
	free (env);
	exit (status);
}
