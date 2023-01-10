/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:37:07 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/10 15:05:47 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtin_pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 1025);
	if (path == NULL)
	{
		ft_putstr_fd("Error: ", fd);
		ft_putstr_fd(strerror(errno), fd);
		ft_putchar_fd('\n', fd);
		free(path);
	}
	else
	{
		ft_putstr_fd(path, fd);
		ft_putchar_fd('\n', fd);
	}
	free (path);
}
