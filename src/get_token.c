/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:19:39 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/10 11:59:38 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_word(int *i, char *line)
{
	int		final;
	char	*word;
	int		init;

	final = *i;
	if (ft_is(line[final], "\"") || ft_is(line[final], "\'"))
	{
		final++;
		init = final;
		final = quotation_marks(i, line);
		if (!final)
			return (FALSE);
		word = ft_substr(line, init, final - init);
		*i = final + 1;
	}
	if (!ft_is(line[final], "\"") && !ft_is(line[final], "\'"))
	{
		while (!ft_is(line[final], SPACES_OPERATORS))
			final++;
		word = ft_substr(line, *i, final - *i);
		*i = final;
	}
	return (word);
}

char	*get_operator(int *i, char *line)
{
	char	*redir;

	if ((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '>' && line[*i + 1] == '>'))
	{
		redir = ft_substr(line, *i, 2);
		*i += 1;
	}
	else
		redir = ft_substr(line, *i, 1);
	*i += 1;
	return (redir);
}

char	*get_token(char *line, int reset)
{
    static int     	i = 0;

	if (reset)
		i = 0;
    while (line[i])
    {
		if (!ft_is(line[i], SPACES_OPERATORS))
			return (get_word(&i, line));
		if (ft_is(line[i], OPERATORS))
			return (get_operator(&i, line));
        i++;
    }
	return(NULL);
}
