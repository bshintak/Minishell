/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/16 10:38:22 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(char *line)
{
	char	*path;

	while (*line != ' ')
		line++;
	line++;
	printf ("line: %s\n", line);
	path = getcwd(NULL, 1025);
	printf("old path: %s\n", path);
	if (chdir(line) == -1)
		printf("error\n");
	path = getcwd(NULL, 1025);
	printf("new path: %s\n", path);
}
