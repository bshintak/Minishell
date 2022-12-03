/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_something.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:02:34 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:23:29 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_command(t_node *node, char *token)
{
	char	**wtv;

	if (!node && !token)
		return ;
	wtv = node->data;
	node->data = update_string(wtv, token);
}

void	put_redir(t_node *node, char *token)
{
	if (!node && !token)
		return ;
	node->data = ft_strdup(token);
}

void	put_herdoc(t_node *node, char *token)
{
	if (!node && !token)
		return ;
	node->data = ft_strdup(token);
}
