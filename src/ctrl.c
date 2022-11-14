/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:33:05 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/14 11:44:28 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

void	all_ctrl(void)
{
	signal(SIGINT, ctrl_c);
}

void	ctrl_slash()
{
	sigset_t	slash;
	
	sigemptyset(&slash);
}