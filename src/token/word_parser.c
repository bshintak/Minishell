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

int	needs_of_token(char *token, t_quotes *quo)
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
	{
		quo->simple_quo = simple_quote;
		quo->double_quo = double_quote;
		return (DOLLAR_QUOTE);
	}
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


char	*dollar_and_quotes(char	*token, char **env, t_quotes *quo)
{
	int			i;
	int			final;
	char		*new_token;

	(void)env;
	i = 0;
	final = 1;
	new_token = NULL;
	printf("simple quote = %d\n", quo->simple_quo);
	printf("double quote = %d\n", quo->double_quo);
	if ((token[i] == '\"' || token[i] == '\'') && token[i + 1] != '$')
	{
		while (token[i] && (quo->simple_quo > 0 || quo->double_quo > 0))
		{
			if (token[i] == '\"')
			{
				final = pos_final('\"', token);
				printf("final = %d\n", final);
				if (quo->double_quo > 0)
				{
					quo->double_quo -= 2;
				}
			}
			if (token[i] == '\'')
			{
				final = pos_final('\'', token);
				if (quo->simple_quo > 0)
				{
					quo->simple_quo -= 2;
				}
			}
			i++;
		}
	}
	new_token = ft_substr(token, i, final);
	printf("new_word = %s\n", new_token);
	return (new_token);
}

char	*word_parser(char *token, char **env)
{
	char	*home;
	t_quotes	*quo;
	char	*dollar;

	quo = malloc(sizeof(t_quotes));
	if (!quo)
		return (0);
	quo->simple_quo = 0;
	quo->double_quo = 0;
	home = get_til(token, env);
	if (home)
	{
		if (token)
			free(token);
		token = home;
	}
	if (needs_of_token(token, quo) == MISSING_QUOTE)
		ret_without_error("ERROR: missing quote\n");
	else if (!needs_of_token(token, quo))
		return (token);
	//dollar_and_quotes(token, env, quo);
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