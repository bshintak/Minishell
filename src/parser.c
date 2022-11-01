/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/01 11:58:06 by bshintak         ###   ########.fr       */
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

	token = NULL;
	while (1)
	{
		token = get_token(line);
		if (!token)
			break ;
		//printf("token = %s\n", token);
	}
	// printf("\n");
}

char *get_word(int *i, char *line)
{
	int	final;
	char *word;

	final = *i;
	while (!ft_is(line[final], SPACES_OPERATORS))
		final++;
	word = ft_substr(line, *i, final - *i);
	*i = final;
	printf("word = %s\n", word);
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
	(*i)++;
	printf("redir = %s\n", redir);
	return (redir);
}

char	*get_token(char *line)
{
    static int     	i = 0;

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
