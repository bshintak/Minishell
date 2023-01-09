/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:00 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/09 12:57:57 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is(char c, char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0' && c != set[i])
		i++;
	if (c == set[i])
		return (TRUE);
	return (FALSE);
}

int	quotation_marks(char *line, char quote)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (0);
}

int	num_of_dol(char *dollar)
{
	char	*aux;
	int		i;
	int		ret;

	aux = dollar;
	i = -1;
	ret = 0;
	while (aux[++i])
	{
		if (aux[i] == '$')
			ret++;
	}
	return (ret);
}
