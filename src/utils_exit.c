/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:19:07 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/16 12:29:12 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_exit(int status, int option)
{
	t_exit	*node;
	int		ret;

	ret = 0;
	node = NULL;
	if (option == SET_EXIT)
	{
		ret = status;
		node->status_exit = status;
	}
	if (option == CLEAR_EXIT)
		ret = 0;
	return (ret);
}
