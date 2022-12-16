/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:37:26 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/16 12:42:24 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_exit(char	*dollar, int *i, char *ret)
{
	t_exit	*node;
	char	*wtv;
	char	*final;
	int		size;
	int		index;

	node = malloc(sizeof(t_exit));
	if (!node)
		ret_error("ERROR: Memory allocation failed.\n");
	index = *i;
	size = size_env(&dollar[index + 1]);
	final = ft_strdup(&dollar[(index + 1) + (size + 1)]);
	wtv = ft_strdup(ft_itoa(set_exit(node->status_exit, GET_EXIT)));
	ret = join_tokens(ret, wtv);
	ret = join_tokens(ret, final);
	return (ret);
}
