/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:35:18 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/22 15:21:48 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char *line)
{
	int	i;
	int	len;
	int	new_line;

	i = 4;
	new_line = 0;
	len = ft_strlen(line);
	while (is_space(line[i]))
		i++;
	if (line[i] == '-')
	{
		if (line[i + 1] == 'n' && line[i + 2] == ' ')
			new_line = 1;
		i += 3;
	}
	while (len > i)
	{
		while (line[i] == '"')
			i++;
		printf("%c", line[i++]);
	}
	if (new_line == 0)
		printf("\n");
}
