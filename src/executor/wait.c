/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:18:22 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/11 16:46:36 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_cmd(int pid, int num)
{
	int	status;
	int	n_cmd;

	n_cmd = num;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*exit_status()).i = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		(*exit_status()).i = WTERMSIG(status) + 128;
		if ((*exit_status()).i == 130)
			ft_putstr_fd("\n", 2);
		else if ((*exit_status()).i == 131)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	while (n_cmd)
	{
		wait(NULL);
		n_cmd--;
	}
}
