/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:10:12 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/27 17:41:25 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_line(char **argv)
{
	char	*line;
	int		i;
	//int		fd;

	i = 0;
	line = readline("➜  MiniShell: ");
	if (!line)
		printf("error\n");
	if (line)
	{
		add_history(line);
		while (is_space(line[i]) == 1)
			i++;
		//fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//dup2(fd, STDOUT_FILENO);
		find_builtin(line + i);
	}
}
