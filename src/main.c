/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/07 13:07:03 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		**env_copy;
	t_node		*tree;
	// int			i = -1;

	tree = NULL;
	if (argc != 1 && argv[1])
	{
		printf("wrong argument!\n");
		return (-1);
	}
	env_copy = get_env(env);
	get_signal(SIGQUIT, SIG_IGN);
	get_signal(SIGINT, ctrl_c);
	while (1)
	{
		line = readline("➜  bshintak&&lleiria-MiniShell: ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (!ft_strncmp(line, "exit", 5))
		{
			free (line);
			rl_clear_history();
			return (0);
		}
		add_history(line);
		tree = parser(line, env_copy);
		// print2d(tree);
		if (tree)
		{
			executor(&tree, &env_copy);
			// tree_free(tree);
		}
	}
	return (0);
}
