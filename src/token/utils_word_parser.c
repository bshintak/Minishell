/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_word_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:17:45 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/12 11:52:15 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	word_size_parser(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '$')
			return (i);
	}
	return (i);
}

int	is_permited_env(char c, int i)
{
	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	else if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	else
		return (0);
}

int	size_env(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_permited_env(str[i], i))
			return (i);
	}
	return (i);
}

int	size_parser(char *s)
{
	int	i;

	i = -1;
	if (ft_strchr("\'\"", s[0]))
	{
		i = 0;
		while (s[++i])
		{
			if (s[i] == s[0])
				return (i + 1);
		}
		return (0);
	}
	else
	{
		while (s[++i])
		{
			if (s[i] == '\'' || s[i] == '\"')
				return (i);
		}
		return (i);
	}
	return (0);
}
