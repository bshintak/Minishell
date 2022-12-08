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

char	*update_dollar(char *dollar, char **env, int *i, char *ret)
{
	int		index;
	int		size;
	char	*elm_env;
	char	*final;

	index = *i;
	size = size_env(&dollar[index + 1]);
	if (!size)
		ret = join_char(ret, dollar[index]);
	else
	{
		final = &dollar[index + (size + 1)];
		elm_env = expand_dollar(&dollar[index + 1], env);
		ret = join_exp(ret, elm_env);
		ret = join_exp(ret, final);
	}
	return (ret);
}

char	*update_quote_dollar(char *dollar, char **env)
{
	char	*ret;
	int		size;
	int		i;

	i = -1;
	size = 0;
	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	while (dollar[++i])
	{
		if (dollar[i] != '$')
		{
			size = word_size_parser(&dollar[i]);
			ret = join_tokens(ret, ft_substr(&dollar[i], 0, size));
			i += size - 1;
		}
		else if (dollar[i] == '$')
		{
			ret = update_dollar(dollar, env, &i, ret);
			return (ret);
		}
	}
	free (dollar);
	return (ret);
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
		if (ft_strchr("\"\'", tk[index]))
		{
			aux = ft_substr(&tk[index + 1], 0, size - 2);
			if (tk[index] == '\"')
				aux = update_quote_dollar(aux, env);
		}
		else
		{
			aux = ft_substr(&tk[index], 0, size);
			aux = update_quote_dollar(aux, env);
		}
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
		printf("ERROR: missing quote\n");
	if (!needs_of_token(token))
		return (token);
	dollar = ft_calloc(1, sizeof(char));
	if (!dollar)
		return (NULL);
	while (token[++i])
		dollar = dollar_quotes(token, dollar, env, &i);
	//else
	//	dollar = update_dollar(token, env);
	//if (dollar)
	//{
	//	if (token)
	//		free(token);
	//	token = dollar;
	//}
	//free(quo);
	//free(token);
	return (dollar);
}