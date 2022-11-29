/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:23:21 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:17:41 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_id(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (len == 1)
	{
		if (token[0] == '>')
			return (ID_OUTPUT_REDIR);
		else if (token[0] == '<')
			return (ID_INPUT_REDIR);
		else if (token[0] == '|')
			return (ID_PIPE);
	}
	else if (len == 2)
	{
		if (token[0] == '<' && token[1] == '<')
			return (ID_INPUT_HERDOC);
		else if (token[0] == '>' && token[1] == '>')
			return (ID_OUTPUT_APPEND);
	}
	return (ID_WORD);
}
