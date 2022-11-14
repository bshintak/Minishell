/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/14 11:22:35 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(char *line, t_node *tree)
{
	char	*token;
	int		reset;
	int		id;

	token = NULL;
	reset = 1;
	id = 0;
	while (1)
	{
		token = get_token(line, reset);
		if (!token)
			break ;
		printf("token = %s\n", token);
		id = get_id(token);
		printf("id = %d\n", id);
		reset = 0;
	}
}
