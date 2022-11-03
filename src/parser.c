/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/03 14:44:38 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is(char c, char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0' && c != set[i])
		i++;
	if (c == set[i])
		return (1);
	return (0);
}

void	get_id(char *word)
{
	t_token	*wtv;
	if (word[0] == '>' || word[0] == '<')
		wtv->id = ID_REDIR;
	else if (word[0] == '|')
		wtv->id = ID_PIPE;
	else
		wtv->id = ID_WORD;
}

void	parser(char *line)
{
	char	*token;
	int		reset;

	token = NULL;
	reset = 1;
	while (1)
	{
		token = get_token(line, reset);
		if (!token)
			break ;
		printf("token = %s\n", token);
		reset = 0;
	}
}

int	quotation_marks(int *i, char *line)
{
	int		aux;
	char	*mark;

	aux = *i;
	if (line[*i] == '\"')
	{
		aux++;
		while(line[aux] != '\"' && line[aux])
			aux++;
		if (line[aux] != '\"')
			return (FALSE);
	}
	if (line[*i] == '\'')
	{
		aux++;
		while(line[aux] != '\'' && line[aux])
			aux++;
		if (line[aux] != '\'')
			return (FALSE);
	}
	return (aux);
}

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
			return(FALSE);
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
	return(word);
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
