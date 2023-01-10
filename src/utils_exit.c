/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:19:07 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/10 11:59:35 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exit	*exit_status(void)
{
	static t_exit	exit_status;

	return (&exit_status);
}

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
