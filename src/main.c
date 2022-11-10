/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/10 12:30:42 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	char 		*line;

	if (argc != 1 && argv[1])
	{
		printf("wrong argument!\n");
		return (-1);
	}
	while (1)
	{
		line = readline("➜  MiniShell: ");
		if (!line)
			return (printf("error\n"));
		add_history(line);
		find_builtin(line);
		parser(line);
	}
	return (0);
}
