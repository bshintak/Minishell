/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:10:12 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/22 15:47:41 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_line(void)
{
	char	*line;

	line = readline("➜  MiniShell: ");
	if (!line)
		printf("error\n");
	if (line)
	{
		add_history(line);
		//exec_line(line);
	}
}