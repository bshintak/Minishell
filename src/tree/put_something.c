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
	t_command *wtv;

	if (!node && !token)
		return ;
	if (!node->data)
	{
		wtv = malloc(sizeof(t_command));
		if (!wtv)
			ret_error("ERROR: Memory allocation failed.\n");
		wtv->cmd = NULL;
	}
	else
	{
		wtv = (t_command *)node->data;
		wtv->cmd = update_string(wtv->cmd, token);
		node->data = (void *)wtv;
	}
}

void	put_redir(t_node *node, char *token)
{
	t_redir	*wtv;
	
	if (!node && !token)
		return ;
	wtv = malloc(sizeof(t_redir));
	if (!wtv)
		ret_error("ERROR: Memory allocation failed.\n");
	wtv->redir = ft_strdup(token);
	node->data = (void *)wtv;
}

void	put_herdoc(t_node *node, char *token)
{
	t_herdoc	*wtv;
	
	if (!node && !token)
		return ;
	wtv = malloc(sizeof(t_herdoc));
	if (!wtv)
		ret_error("ERROR: Memory allocation failed.\n");
	wtv->herdoc = ft_strdup(token);
	node->data = (void *)wtv;
}
