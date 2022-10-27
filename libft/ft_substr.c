/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:01:04 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/27 18:11:43 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s) + 1;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		ptr[j++] = s[i++];
	ptr[j] = 0;
	return (ptr);
}
