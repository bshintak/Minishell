/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:34:59 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/25 12:15:09 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	have_value(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i] != '\0')
	{
		if (env_line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (have_value(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
}
