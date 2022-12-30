/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:36:17 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/30 16:36:46 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fail_malloc2(void *str)
{
	if (!str)
	{
		ft_putendl_fd("minishell: Out of memory!", 2);
		exit(EXIT_FAILURE);
	}
}

void	fail_malloc(char **str)
{
	if (!str)
	{
		ft_putendl_fd("minishell: Out of memory!", 2);
		exit(EXIT_FAILURE);
	}
}
