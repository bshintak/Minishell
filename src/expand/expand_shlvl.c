/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:41:32 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/12 11:42:40 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_shlvl(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6))
		i++;
	if (env[i])
		return (env[i] + 6);
	return (NULL);
}
