/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/10 19:35:01 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	char 		*line;
	char 		**env_copy;
	t_node		*tree;
	int			i;

	i = -1;
	if (argc != 1 && argv[1])
	{
		printf("wrong argument!\n");
		return (-1);
	}
	env_copy = get_env(env);
	while (env_copy[++i])
		printf("%s\n", env_copy[i]);
	while (1)
	{
		line = readline("➜  MiniShell: ");
		if (!line)
			return (printf("error\n"));
		add_history(line);
<<<<<<< HEAD
		parser(line, tree);
=======
		find_builtin(line);
		parser(line);
>>>>>>> b1e579e1289a2c4fd3cd75c867764ee0aaa442f3
	}
	return (0);
}
