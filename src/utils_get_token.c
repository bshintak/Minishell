/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:00 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/03 15:21:34 by bshintak         ###   ########.fr       */
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
