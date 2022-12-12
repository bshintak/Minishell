/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:40:23 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/12 15:02:50 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_dollar(char *token, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!token)
		return (NULL);
	size = size_parser(token);
	while (env[i] && ft_strncmp(env[i], token, size))
		i++;
	if (env[i])
		return (env[i] + size + 1);
	return (NULL);
}
