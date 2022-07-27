/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:35:18 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/27 11:47:39 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'e' && line[i + 1] == 'c' 
		&& line[i + 2] == 'h' && line[i + 3] == 'o')
		i += 5;
	while (line[i])
		printf("%c", line[i++]);
	printf("\n");
}