/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:52:54 by bshintak          #+#    #+#             */
/*   Updated: 2022/07/27 18:20:18 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(void)
{
	char	*pwd;
	char	*ret;
	int		len;
	int		i;
	
	i = 0;
	pwd = getcwd(NULL, 0);
	len = ft_strlen(pwd);
	while (pwd[len] != '/')
		len--;
	while (pwd[--len])
		printf("%c", pwd[i++]);
	printf("\n");
}
