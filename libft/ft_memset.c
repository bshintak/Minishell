/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:17:00 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/12 11:17:01 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bass;

	i = 0;
	bass = (unsigned char *)s;
	while (i < n)
	{
		bass[i] = c;
		i++;
	}
	return (s = bass);
}
