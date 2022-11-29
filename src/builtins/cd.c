/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/17 13:57:15 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	builtin_cd(void)
// {
// 	char	*path;
	
// 	path = getcwd(NULL, 1025);
// 	printf("path: %s\n", path);

	
// }

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

// int main(void)
// {
// 	builtin_cd();
// 	return (0);
// }