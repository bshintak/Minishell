/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:04:29 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:25:22 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	needs_of_token(char *token)
{
	int	i;
	int	simple_quote;
	int	double_quote;
	int	dollar;

	i = -1;
	simple_quote = 0;
	double_quote = 0;
	dollar = 0;
	while (token[++i])
	{
		if (ft_is(token[i], "\""))
			simple_quote++;
		if (ft_is(token[i], "\'"))
			double_quote++;
		if (ft_is(token[i], "$"))
			dollar++;
	}
	if ((simple_quote % 2 != 0) || (double_quote % 2 != 0))
		return (MISSING_QUOTE);
	else if (dollar || simple_quote > 1 || double_quote > 1)
		return (DOLLAR_QUOTE);
	return (0);
}

char	*word_parser(char *token, char **env)
{
	char	*home;

	home = get_til(token, env);
	if (home)
	{
		if (token)
			free(token);
		token = home;
	}
	if (!needs_of_token(token))
		return (token);
	if (needs_of_token(token) == MISSING_QUOTE)
		ret_error("ERROR: missing quote!\n");
	return (token);
}