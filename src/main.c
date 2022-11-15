/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/15 16:20:05 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
	char 		*line;
	char 		**env_copy;
	t_node		*tree;
	// int			i;

	// i = -1;
	// (void)env;
	tree = NULL;
	if (argc != 1 && argv[1])
	{
		printf("wrong argument!\n");
		return (-1);
	}
	env_copy = get_env(env);
	// while (env_copy[++i])
	// 	printf("%s\n", env_copy[i]);
	ctrl_slash();
	while (1)
	{
		line = readline("➜  bshintak&&lleiria-MiniShell: ");
		if (!line)
			return (printf("error\n"));
		add_history(line);
		// get_signal(SIGINT, ctrl_c);
		// find_builtin(line);
		parser(line, tree, env_copy);
	}
	return (0);
}
