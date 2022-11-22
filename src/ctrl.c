/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:33:05 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/22 14:38:59 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_slash(void)
{
	sigset_t	slash;

	sigemptyset(&slash);
	sigaddset(&slash, SIGQUIT);
	sigprocmask(SIG_BLOCK, &slash, NULL);
}

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		set_exit(EXIT_CTRL_C, SET_EXIT);
	}
}

void	ctrl_d(int signal)
{
	printf("aqui\n");
	if (signal == SIGQUIT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\nexit\n", STDOUT_FILENO);
		set_exit(0, CLEAR_EXIT);
	}
}

void	get_signal(int signal, void (*function)())
{
	struct sigaction	wtv;

	sigemptyset(&(wtv.sa_mask));
	wtv.sa_flags = 0;
	wtv.sa_handler = function;
	if (sigaction(signal, &wtv, NULL) == -1)
		ret_error("ERROR: sigaction\n");
}
