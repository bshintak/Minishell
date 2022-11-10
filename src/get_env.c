/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:18:02 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/10 19:35:27 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_shlvl(char *line)
{
	char	*copy;
	char	*ret;

	copy = ft_itoa(ft_atoi(line + 6) + 1);
	ret = ft_strjoin("SHLVL=", copy);
	//printf("shlvl = %s\n", ret);
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
	return (copy_env);
}