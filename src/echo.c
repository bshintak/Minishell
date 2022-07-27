/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:35:18 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/27 12:14:34 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'e' && line[i + 1] == 'c' 
		&& line[i + 2] == 'h' && line[i + 3] == 'o')
		i += 5;
	else if (is_space(line [i + 4] == 0) && line[i + 4] != '\0')
	{
		printf("command not found\n");
		return ;
	}
	if (line[5] == '-' && line[6] == 'n')
		i += 3;
	while (line[i])
	{
		if (line[i] == '"')
			i++;
		printf("%c", line[i++]);
	}
	if (!(line[5] == '-' && line[6] == 'n'))
		printf("\n");
}