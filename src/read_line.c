/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:10:12 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/27 11:23:14 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_line(char **argv)
{
	char	*line;
	int		i;

	i = 0;
	line = readline("➜  MiniShell: ");
	if (!line)
		printf("error\n");
	if (line)
	{
		while (is_space(line[i]) == 1)
			i++;
		find_builtin(line + i);
	}
}