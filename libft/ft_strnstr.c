/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:57:28 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/08 11:24:50 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "../minishell.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	n1;
	size_t	n2;

	n1 = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[n1] != '\0')
	{
		n2 = 0;
		while (str[n1 + n2] == to_find[n2] && n1 + n2 < len)
		{
			if (to_find[n2 + 1] == '\0')
				return ((char *)&str[n1]);
			n2++;
		}
		n1++;
	}
	return (NULL);
}
