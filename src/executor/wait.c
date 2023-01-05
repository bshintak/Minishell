/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:18:22 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 15:43:12 by lleiria-         ###   ########.fr       */
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
	// else if (WIFSIGNALED(status))
	// {
	// 	printf("status = %d\n", status);
	// 	(*exit_status()).i = 128 + status;
	// 	if ((*exit_status()).i == 130)
	// 		ft_putstr_fd("\n", STDOUT_FILENO);
	// 	else if ((*exit_status()).i > 130)
	// 		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
	// }
	while (n_cmd)
	{
		wait(NULL);
		n_cmd--;
	}
}

char	*path_cmd(char *cmd, char ***env)
{
	char	*pwd;
	char	*tmp;
	char	**tmp_env;

	tmp_env = *env;
	pwd = NULL;
	tmp = NULL;
	pwd = path_comander(cmd, pwd, tmp, tmp_env);
	if (pwd)
		return (pwd);
	cmd_error(cmd);
	return (NULL);
}
