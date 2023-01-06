/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_update_dol_quo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:50:22 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/06 15:16:47 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*join_tokens(char *token, char *new_token)
{
	char	*ret;

	ret = NULL;
	if (token && new_token)
		ret = ft_strjoin(token, new_token);
	free(token);
	free(new_token);
	return (ret);
}

char	*join_char(char *token, char c)
{
	char	*ret;
	char	aux[2];

	if (!token)
		return (0);
	aux[0] = c;
	aux[1] = '\0';
	ret = ft_strjoin(token, aux);
	free(token);
	return (ret);
}
