/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:16:38 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/05 17:35:57 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_nlen(long int i)
{
	int	count;

	count = 0;
	if (i < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

char	*ft_transform(long int nb, char *s, int len)
{
	if (nb < 0)
	{
		s[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		s[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			len;
	long int	nb;
	char		*s2;

	nb = n;
	if (nb == 0)
	{
		return (ft_strdup("0"));
	}
	len = ft_nlen(nb);
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len--] = 0;
	s2 = ft_transform(nb, s, len);
	return (s2);
}
