/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:18:22 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/30 16:18:48 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_cmd(int pid, int num, char ***env)
{
	int	status;
	int	n_cmd;

	(void)env;
	n_cmd = num;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*exit_status()).i = WEXITSTATUS(status);
	while (n_cmd--)
		wait(NULL);
}
