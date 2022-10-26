/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/26 18:25:44 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*get_token(char *line)
{
    t_token *token;
    static int     i;

    token = malloc(sizeof(t_token));
	token->start = 0;
    while (line[i])
    {
		if (!(ft_strchr(OPERATORS, line[i])))
		{
			token->content = ft_substr(line, token->start, i - token->start);
			token->start = i + 1;
			token->id = ID_OPER;
			return (token->content);
		}
        else if (ft_strchr(SPACES, line[i]))
        {
            token->content = ft_substr(line, token->start, i - token->start);
            token->start = i + 1;
			token->id = ID_WORD;
			return(token->content);
        }
        i++;
    }
	return(NULL);
}
