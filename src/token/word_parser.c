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

char	*update_dollar(char *token, char **env)
{
	char	*dollar;
	int		i;

	i = -1;
	dollar = NULL;
	while(token[++i])
	{
		if (token[i] == '$' && token[i + 1] == '?')
			dollar = find_shlvl(env);
		else if (token[i] == '$' && token[i + 1] != '?')
			dollar = expand_dollar(token + 1, env);
	}
	return (dollar);
}

char	*remove_quotes(char *token, int *i)
{
	int	index;
	int	final;

	index = *i;
	final = 0;
	if (token[index] == '\"')
		final = pos_final('\"', token);
	printf("final = %d\n", final);
	return(NULL);
}

char	*dollar_and_quotes(char	*token, char **env)
{
	int	i;
	char	*new_token;

	(void)env;
	i = -1;
	while (token[++i])
	{
		if ((token[i] == '\"' || token[i] == '\'') && token[i + 1] != '$')
			new_token = remove_quotes(token, &i);
		return (new_token);
	}
	return (NULL);
}

char	*word_parser(char *token, char **env)
{
	char	*home;
	char	*dollar;

	home = get_til(token, env);
	if (home)
	{
		if (token)
			free(token);
		token = home;
	}
	if (needs_of_token(token) == MISSING_QUOTE)
		ret_without_error("ERROR: missing quote\n");
	else if (!needs_of_token(token))
		return (token);
	//dollar_and_quotes(token, env);
	else
		dollar = update_dollar(token, env);
	if (dollar)
	{
		if (token)
			free(token);
		token = dollar;
	}
	return (token);
}