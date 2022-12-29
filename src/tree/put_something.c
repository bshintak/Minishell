/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_something.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:02:34 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/29 15:44:44 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_command(t_node *node, char *token)
{
	char	**wtv;

	wtv = node->data;
	node->data = update_string(wtv, token);
}

void	put_redir(t_node *node, char *token)
{
	node->data = ft_strdup(token);
}
