/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:04:29 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/30 16:14:26 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	needs_of_token(char *token)
{
	int			i;
	int			simple_quote;
	int			double_quote;
	int			dollar;

	i = -1;
	simple_quote = 0;
	double_quote = 0;
	dollar = 0;
	while (token[++i])
	{
		if (ft_is(token[i], "\""))
			double_quote++;
		if (ft_is(token[i], "\'"))
			simple_quote++;
		if (ft_is(token[i], "$"))
			dollar++;
	}
	if ((simple_quote % 2 != 0) || (double_quote % 2 != 0))
		return (MISSING_QUOTE);
	else if (dollar || simple_quote > 1 || double_quote > 1)
		return (DOLLAR_QUOTE);
	return (0);
}

char	*dollar_quotes2(char *tk, int size, char **env, int *i)
{
	int		index;
	char	*aux;

	index = *i;
	aux = NULL;
	if (ft_strchr("\"\'", tk[index]))
	{
		aux = ft_substr(&tk[index + 1], 0, size - 2);
		fail_malloc2(aux);
		if (tk[index] == '\"')
			aux = update_quote_dollar(aux, env);
	}
	else
	{
		aux = ft_substr(&tk[index], 0, size);
		fail_malloc2(aux);
		aux = update_quote_dollar(aux, env);
	}
	return (aux);
}

char	*dollar_quotes(char *tk, char *dol, char **env, int *i)
{
	int		size;
	int		index;
	char	*aux;

	index = *i;
	aux = NULL;
	size = size_parser(&tk[index]);
	if (size)
	{
		aux = dollar_quotes2(tk, size, env, &index);
		dol = join_tokens(dol, aux);
		*i += size - 1;
	}
	else
		dol = join_char(dol, tk[index]);
	return (dol);
}

char	*word_parser(char *token, char **env)
{
	char		*home;
	char		*dollar;
	int			i;

	i = -1;
	home = get_til(token, env);
	if (home)
	{
		if (token)
			free(token);
		token = home;
	}
	if (needs_of_token(token) == MISSING_QUOTE)
		print_error_quote(token, MISSING_QUOTE);
	if (!needs_of_token(token))
		return (token);
	dollar = ft_calloc(1, sizeof(char));
	if (!dollar)
		fail_malloc2(dollar);
	while (token[++i])
		dollar = dollar_quotes(token, dollar, env, &i);
	free(token);
	return (dollar);
}
