/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:19:07 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/19 11:47:01 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_exit(int status, int option)
{
	int		ret;

	ret = 0;
	if (option == SET_EXIT)
	{
		ret = status;
		((*exit_status()).i) = status;
	}
	if (option == CLEAR_EXIT)
		ret = 0;
	return (ret);
}
