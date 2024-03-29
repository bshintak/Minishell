/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/04 15:15:53 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*error_parser(char *token)
{
	(*exit_status()).i = 2;
	if (token)
		free (token);
	return (NULL);
}

t_node	*parser(char *line, char **env)
{
	t_node	*tree;
	char	*token;
	int		reset;
	int		id;

	tree = NULL;
	token = NULL;
	reset = 1;
	while (1)
	{
		token = get_token(line, reset);
		if (syntax_error(tree, token))
			return (error_parser(token));
		if (!token)
			break ;
		id = get_id(token);
		if (id == ID_WORD)
			token = word_parser(token, env, 0);
		create_tree(&tree, token, id);
		if (token)
			free (token);
		reset = 0;
	}
	return (tree);
}
