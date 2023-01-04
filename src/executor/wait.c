/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:18:22 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/03 15:23:12 by bshintak         ###   ########.fr       */
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
		printf("status = %d\n", status);
		(*exit_status()).i = 128 + status;
		if ((*exit_status()).i == 130)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if ((*exit_status()).i > 130)
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
	}
	while (n_cmd)
	{
		wait(NULL);
		n_cmd--;
	}
}
