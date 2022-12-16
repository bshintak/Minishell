/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:03:28 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/16 17:57:53 by bshintak         ###   ########.fr       */
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
	while(line[++i])
	{
		if (ft_isascii(line[i]) && !ft_isdigit(line[i]))
			return (2);
	}
	i = 0;
	if (ft_isdigit(line[i]))
		return (num_exit(ft_atoi(line)));
	return (0);
}

void	builtin_exit(char **line)
{
	int	status;

	status = 0;
	if (!line[1])
	{
		printf("exit\n");
		status = 0;
	}
	else
		status = type_exit(line[1]);
	exit (status);
}
