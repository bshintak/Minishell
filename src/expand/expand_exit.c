/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:37:26 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/27 12:44:07 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_exit(char	*dollar, int *i, char *ret)
{
	char	*wtv;
	char	*final;
	char	*itoa_s;
	int		size;
	int		index;

	index = *i;
	size = size_env(&dollar[index + 1]);
	final = ft_strdup(&dollar[(index + 1) + (size + 1)]);
	itoa_s = ft_itoa(set_exit((*exit_status()).i, GET_EXIT));
	wtv = ft_strdup(itoa_s);
	free (itoa_s);
	ret = join_tokens(ret, wtv);
	ret = join_tokens(ret, final);
	return (ret);
}
