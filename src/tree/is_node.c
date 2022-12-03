/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:46:34 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/03 14:54:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_command(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_COMMAND || node->id == ID_BUILTIN)
		return (1);
	return (0);
}

int	is_pipe(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_PIPE)
		return (1);
	return (0);
}

int	is_redir(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_INPUT_REDIR || node->id == ID_OUTPUT_REDIR
		|| node->id == ID_OUTPUT_APPEND || node->id == ID_INPUT_HERDOC)
		return (1);
	return (0);
}

int	is_herdoc(t_node *node)
{
	if (!node)
		return (0);
	if (node->id == ID_INPUT_HERDOC)
		return (1);
	return (0);
}
