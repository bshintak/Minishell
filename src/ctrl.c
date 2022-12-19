/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:33:05 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:11:11 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prep_act(struct sigaction *act, char si_mode)
{
	ft_memset(act, '\0', sizeof(*act));
	act->sa_flags = SA_SIGINFO;
	sigemptyset(&act->sa_mask);
	if (si_mode == SI_IGN)
		(act->sa_handler) = SIG_IGN;
	//else if (si_mode == SI_HDOC)
	//	(act->sa_sigaction) = handle_signals_heredoc;
	else if (si_mode == SI_RLINE)
		(act->sa_sigaction) = ctrl_c;
	else if (si_mode == SI_DFL)
		(act->sa_handler) = SIG_DFL;
	else
		return ;
}

void	call_sigact(char act_choice)
{
	struct sigaction	act;

	prep_act(&act, act_choice);
	if (sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
	{
		exit(1);
	}
}

void	ctrl_c(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		set_exit(EXIT_CTRL_C, SET_EXIT);
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
