/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:37:14 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/27 12:40:21 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*update_dollar(char *dollar, char **env, int *i, char *ret)
{
	int		index;
	int		size;
	char	*elm_env;
	char	*final;

	index = *i;
	size = size_env(&dollar[index + 1]);
	if (!size)
		return (dollar);
	else
	{
		final = ft_strdup(&dollar[index + (size + 1)]);
		elm_env = ft_strdup(expand_dollar(&dollar[index], env));
		ret = join_tokens(ret, elm_env);
		ret = join_tokens(ret, final);
	}
	return (ret);
}

char	*do_dollar(char *dollar, char **env, int *i, char *ret)
{
	int	index;

	index = *i;
	if (dollar[index] == '$' && dollar[index + 1] != '?')
		ret = update_dollar(dollar, env, &index, ret);
	else if (dollar[index] == '$' && dollar[index + 1] == '?')
		ret = get_exit(dollar, &index, ret);
	return (ret);
}

char	*update_quote_dollar(char *dollar, char **env)
{
	char	*ret;
	int		size;
	int		i;

	i = -1;
	ret = ft_calloc(1, sizeof(char));
	fail_malloc2(ret);
	while (dollar[++i])
	{
		if (dollar[i] != '$')
		{
			size = word_size_parser(&dollar[i]);
			ret = join_tokens(ret, ft_substr(&dollar[i], 0, size));
			i += size - 1;
		}
		else if (dollar[i] == '$' && (dollar[i + 1] == '\'' || dollar[i + 1] == '\"'))
		{
			free (ret);
			return (dollar);
		}
		else if (dollar[i] == '$' && dollar[i + 1])
		{
			ret = do_dollar(dollar, env, &i, ret);
			break ;
		}
	}
	free (dollar);
	return (ret);
}

char	*join_tokens(char *token, char *new_token)
{
	char	*ret;

	ret = NULL;
	if (token && new_token)
		ret = ft_strjoin(token, new_token);
	free(token);
	free(new_token);
	return (ret);
}

char	*join_char(char *token, char c)
{
	char	*ret;
	char	aux[2];

	if (!token)
		return (0);
	aux[0] = c;
	aux[1] = '\0';
	ret = ft_strjoin(token, aux);
	free(token);
	return (ret);
}
