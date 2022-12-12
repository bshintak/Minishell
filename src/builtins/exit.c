/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:03:28 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/12 15:00:09 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	num_exit(char *line, int *index)
{
	int		i;
	int		len;
	char	*num;

	i = *index;
	len = 0;
	while (line[i] && ft_isdigit(line[i]))
	{
		len++;
		i++;
	}
	num = ft_substr(line, *index, len);
	return (set_exit(ft_atoi(num), SET_EXIT));
}

int	ft_exit(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (ft_isalpha(line[i]))
		return (set_exit(2, SET_EXIT));
	if (ft_isdigit(line[i]))
		return (num_exit(line, &i));
	return (0);
}
