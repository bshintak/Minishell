/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:04:29 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/06 15:00:22 by bshintak         ###   ########.fr       */
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


char	*dollar_and_quotes2(char *token, char **env, t_quotes *quo)
{
	int		i;
	int		size;
	char	*new_token;

	(void)env;
	i = 0;
	new_token = NULL;
	size = ft_strlen(token);
	if ((token[i] == '\"' || token[i] == '\'') && token[i + 1] != '$')
	{
		while (token[i] && (quo->simple_quo > 0 || quo->double_quo > 0))
		{
			if (token[i] == '\"')
			{
				if (token[size - 1] == '\"')
					size--;
				printf("size = %d\n", size);
				if (quo->double_quo > 0)
					quo->double_quo -= 2;
			}
			if (token[i] == '\'')
			{
				if (token[size - 1] == '\'')
					size--;
				if (quo->simple_quo > 0)
					quo->simple_quo -= 2;
			}
			i++;
		}
	}
	new_token = ft_substr(token, i, size - i);
	printf("new_word = %s\n", new_token);
	return (new_token);
}

char	*remove_quotes(char *token, int *i)
{
	int		index;
	char	*new_str;

	index = *i;
	new_str = NULL;
	if (token[index] == '\"')
	{
		index++;
		while (token[index] != '\"')
			index++;
		if (token[index] == '\"')
			new_str = ft_substr(token, *i + 1, index - 1);
	}
	else if (token[index] == '\'')
	{
		index++;
		while(token[index] != '\'')
			index++;
		if (token[index] == '\'')
			new_str = ft_substr(token, *i + 1, index - 1);
	}
	return (new_str);
}

char	*dollar_and_quotes(char *token, t_quotes *quo)
{
	int		i;
	char	*new_str;
	int		size;

	i = -1;
	new_str = NULL;
	size = ft_strlen(token) - 1;
	while (token[++i])
	{
		if (token[i] == '\"' || token[i] == '\'')
		{
			if ((quo->simple_quo == 2 && quo->double_quo == 0)
				|| (quo->simple_quo == 0 && quo->double_quo == 2))
			{
				new_str = ft_substr(token, i + 1, size - 1);
				break ;
			}
			else
			{
				new_str = remove_quotes(token, &i);
				break ;
			}
		}
	}
	i = -1;
	while (new_str[++i])
	{
		if (new_str[i] == '\"' || new_str[i] == '\'')
			dollar_and_quotes(new_str, quo);
	}
	printf("new_word = %s\n", new_str);
	return (new_str);
}

char	*word_parser(char *token, char **env)
{
	char	*home;
	t_quotes	*quo;
	// char	*dollar;

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
	// if (needs_of_token(token, quo) == MISSING_QUOTE)
	// 	ret_without_error("ERROR: missing quote\n");
	if (!needs_of_token(token, quo))
		return (token);
	dollar_and_quotes(token, quo);
	// printf("dollar = %s\n", dollar);
	// else
	// 	dollar = update_dollar(token, env);
	// if (dollar)
	// {
	// 	if (token)
	// 		free(token);
	// 	token = dollar;
	// }
	return (token);
}