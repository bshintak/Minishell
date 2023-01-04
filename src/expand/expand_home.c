/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:43:17 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/04 15:15:29 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_home(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "HOME=", 5))
		i++;
	if (env[i])
		return (env[i] + 5);
	return (NULL);
}

char	*get_til(char *token, char **env, int status)
{
	int		token_size;
	char	*home;

	home = NULL;
	if (status == REDIR)
		return (NULL);
	if (!token || !env)
		return (NULL);
	token_size = ft_strlen(token);
	if ((token[0] == '~' && token_size == 1)
		|| (token[0] == '~' && token[1] == '/' && token_size == 2))
		home = find_home(env);
	return (home);
}
