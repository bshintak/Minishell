/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:58:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/27 18:43:11 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_token(void *tok)
{
	t_token *token = (t_token *)tok;
	printf("%d: %s\n", token->id, token->content);
}

int main(int argc, char **argv)
{
	char 		*line;
	t_list		*idk;

	idk = NULL;
	while (1)
	{
		line = readline("➜  MiniShell: ");
		if (!line)
			return (printf("error\n"));
		add_history(line);
		token_list(line, &idk);
		ft_lstiter(idk, print_token);
		// printf("%s\n", token);
		// find_builtin(line);
		ft_lstclear(&idk, free);
	}
}
