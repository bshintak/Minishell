/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:19:07 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/15 16:41:26 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_exit(int status, int option)
{
	int	ret;

	if (option == SET_EXIT)
		ret = status;
	if (option == CLEAR_EXIT)
		ret = 0;
	return (ret);	
}