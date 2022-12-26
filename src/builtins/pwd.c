/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:37:07 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/26 17:01:46 by bshintak         ###   ########.fr       */
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
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	free (path);
}
