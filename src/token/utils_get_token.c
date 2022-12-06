/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:00 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/06 12:15:31 by bshintak         ###   ########.fr       */
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
