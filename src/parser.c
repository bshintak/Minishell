/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/10 12:01:27 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_command(char *token)
// {
// 	return (access(token, F_OK | X_OK));
// }

void	parser(char *line)
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
		// if (id == ID_WORD)
		// 	printf("access = %d\n", check_command(token));
		reset = 0;
	}
}
