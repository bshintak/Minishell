/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:33:05 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/14 13:48:48 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(void)
{
		printf("\n");
}

// void	all_ctrl(void)
// {
// 	signal(SIGINT, ctrl_c);
// }

void	ctrl_slash(void)
{
	// struct sigaction wtv;
	sigset_t	slash;
	
	sigemptyset(&slash);
	sigaddset(&slash, SIGQUIT);
	sigprocmask(SIG_BLOCK, &slash, NULL);
}