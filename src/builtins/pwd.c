/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:37:07 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/29 12:12:47 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 1025);
	if (path == NULL)
		printf("Error: %s\n", strerror(errno));
	else
		printf("%s\n", path);
}
