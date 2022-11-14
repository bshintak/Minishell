/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/11/14 10:54:25 by bshintak         ###   ########.fr       */
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
	if (line[3] == '.')
		chdir("..");
	printf("path: %s\n", path);
}

// int main(void)
// {
// 	builtin_cd();
// 	return (0);
// }