/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:00 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:17:59 by bshintak         ###   ########.fr       */
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

int	pos_final(char c, char *set, int size)
{
	if (!set)
		return (0);
	while (c != set[size] && size > 0)
		size--;
	if (c == set[size])
		return (size);
	return (0);
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
