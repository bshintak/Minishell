/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/05 11:37:27 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*parser(char *line, char **env)
{
	t_node	*tree;
	char	*token;
	int		reset;
	int		id;

	tree = NULL;
	token = NULL;
	reset = 1;
	id = 0;
	while (1)
	{
		token = get_token(line, reset);
		if (!token)
			break ;
		id = get_id(token);
		if (id == ID_WORD)
			token = word_parser(token, env);
		create_tree(&tree, token, id);
		reset = 0;
	}
	return (tree);
}
