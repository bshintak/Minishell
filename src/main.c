/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/10 15:42:50 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_exit(char *line, char **env)
{
	int	i;

	i = -1;
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		rl_clear_history();
		while (env[++i])
			free (env[i]);
		exit((*exit_status()).i);
	}
}

int	wrong_arg(int argc, char **argv)
{
	if (argc != 1 && argv[1])
	{
		ft_putstr_fd("wrong argument!\n", 2);
		return (1);
	}
	return (0);
}

void	tree_parser(char *line, char ***env, t_heredoc *wtv)
{
	t_node		*tree;
	t_node		*inicial_tree;

	tree = parser(line, *env);
	inicial_tree = tree;
	if (inicial_tree)
	{
		while (inicial_tree->up)
			inicial_tree = inicial_tree->up;
	}
	// print2d(tree);
	free (line);
	if (tree)
	{
		executor(&tree, env, num_pipes(tree), wtv);
		tree_free(inicial_tree);
		tree = NULL;
	}
}

void	while_func(char *line, char **env_copy, t_heredoc *wtv)
{
	while (1)
	{
		line = readline("➜  bshintak&&lleiria-MiniShell: ");
		main_exit(line, env_copy);
		if (line)
			add_history(line);
		wtv->line = ft_strdup(line);
		tree_parser(line, &env_copy, wtv);
		free (wtv->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		**env_copy;
	t_heredoc	*wtv;

	line = NULL;
	wtv = malloc(sizeof(t_heredoc));
	if (wrong_arg(argc, argv))
		return (0);
	env_copy = get_env(env);
	if (!env_copy)
		return (0);
	(*exit_status()).i = 0;
	get_signal(SIGQUIT, SIG_IGN);
	get_signal(SIGINT, ctrl_c);
	while_func(line, env_copy, wtv);
	free (wtv);
	free (env_copy);
	return (0);
}
