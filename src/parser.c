/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/27 18:46:43 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_list(char *line, t_list **idk)
{
	int	i;
	t_token *token;
	char	*ptr;

	i = 0;
	while (token)
	{
		ptr = get_token(line, &i);
		if (ptr)
		{
			token = malloc(sizeof(t_token));
			if (!token)
				return ;
			token->content = ptr;
			ft_lstadd_back(idk, ft_lstnew(token));
		}
		else
			return ;
	}
}

int	get_id(char *line)
{
	if (line[0] == '<' || line[0] == '>')
		return (ID_REDIR);
	else if (line[0] == '|')
		return (ID_PIPE);
	return (ID_WORD);
}

int	ft_is(char c, char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0' && (unsigned char)c != set[i])
		i++;
	if ((unsigned char)c == set[i])
		return (1);
	return (0);
}

char	*get_token(char *line, int *i)
{
    int start;
	char *word;

	word = NULL;
	start = *i;
    while (line[*i])
    {
		// ignore spaces
		while (line[*i] && ft_is(line[*i], SPACES))
			(*i)++;
		// set start to first letter
		start = *i;
		while (line[*i] && !ft_is(line[*i], SPACES))
			(*i)++;
		if (start != *i)
		{
			word = ft_substr(line, start, *i - start);
			//printf("{%d, %d} : %s\n", start, *i, word);
		}
		// get word
		if (word)
			return(word);
		// update i
    }
	return(NULL);
}                                                                                                                                                                                                                                                                               
