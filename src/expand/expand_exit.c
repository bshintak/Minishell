/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:37:26 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 17:36:57 by bshintak         ###   ########.fr       */
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
	itoa_s = ft_itoa((*exit_status()).i);
	wtv = ft_strdup(itoa_s);
	free (itoa_s);
	ret = join_tokens(ret, wtv);
	ret = join_tokens(ret, final);
	return (ret);
}
