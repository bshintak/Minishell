/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/29 16:00:59 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exit	*exit_status(void)
{
	static t_exit	exit_status;

	return (&exit_status);
}

void	main_exit(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		rl_clear_history();
		exit((*exit_status()).i);
	}
}

int	wrong_arg(int argc, char **argv)
{
	if (argc != 1 && argv[1])
	{
		printf("wrong argument!\n");
		return (1);
	}
	return (0);
}

int	num_pipes(t_node *tree)
{
	t_node	*node;
	int		num;

	num = 0;
	node = tree;
	if (node->left && !is_redir(node->left))
	{
		num++;
		while (node->left->id == ID_PIPE)
		{
			num++;
			node = node->left;
		}
		// printf("----------%d----------\n", num);
	}
	return (num);
}

void	tree_parser(char *line, char ***env)
{
	t_node		*tree;
	t_node		*inicial_tree;

	tree = parser(line, *env);
	inicial_tree = tree;
	// print2d(tree);
	free (line);
	if (tree)
	{
		executor(&tree, env, num_pipes(tree));
		tree_free(inicial_tree);
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		**env_copy;

	if (wrong_arg(argc, argv))
		return (0);
	env_copy = get_env(env);
	if (!env_copy)
		return (0);
	(*exit_status()).i = 0;
	get_signal(SIGQUIT, SIG_IGN);
	get_signal(SIGINT, ctrl_c);
	while (1)
	{
		// call_sigact(SI_RLINE);
		line = readline("➜  bshintak&&lleiria-MiniShell: ");
		main_exit(line);
		if (line)
			add_history(line);
		tree_parser(line, &env_copy);
	}
	free (env_copy);
	return (0);
}
