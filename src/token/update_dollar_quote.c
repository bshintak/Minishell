/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:37:14 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/30 16:02:04 by bshintak         ###   ########.fr       */
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

char	*no_dollar(char *dollar, char *ret, int *i)
{
	int	index;
	int	size;

	index = *i;
	size = word_size_parser(&dollar[index]);
	ret = join_tokens(ret, ft_substr(&dollar[index], 0, size));
	index += size - 1;
	*i = index;
	return (ret);
}

char	*update_quote_dollar(char *dollar, char **env)
{
	char	*ret;
	int		i;

	i = -1;
	ret = ft_calloc(1, sizeof(char));
	fail_malloc2(ret);
	while (dollar[++i])
	{
		if (dollar[i] != '$')
			ret = no_dollar(dollar, ret, &i);
		else if (dollar[i] == '$'
			&& (dollar[i + 1] == '\'' || dollar[i + 1] == '\"'))
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
