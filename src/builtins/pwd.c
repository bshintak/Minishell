/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:37:07 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 12:19:02 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 1025);
	if (path == NULL)
	{
		ft_putstr_fd("Error: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putchar_fd('\n', 1);
		free(path);
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	free (path);
}
