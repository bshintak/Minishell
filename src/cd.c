/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/09 17:19:52 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	builtin_cd(void)
// {
// 	char	*path;
	
// 	path = getcwd(NULL, 1025);
// 	printf("path: %s\n", path);

	
// }

void	builtin_cd(char *line)
{
	char	*path;
	
	path = getcwd(NULL, 1025);
	chdir(line[3]);
}

int main(void)
{
	builtin_cd();
	return (0);
}