/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:18:02 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/03 15:25:35 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_shlvl(char *line)
{
	char	*copy;
	char	*ret;

	copy = ft_itoa(ft_atoi(line + 6) + 1);
	ret = ft_strjoin("SHLVL=", copy);
	free(copy);
	return (ret);
}

char	**get_env(char **env)
{
	int		i;
	char	**copy_env;

	i = 0;
	while (env[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 1));
	if (!copy_env)
		ret_error("ERROR: Memory allocation failed.\n");
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 7))
			copy_env[i] = get_shlvl(env[i]);
		else
			copy_env[i] = ft_strdup(env[i]);
	}
	copy_env[i] = NULL;
	return (copy_env);
}
