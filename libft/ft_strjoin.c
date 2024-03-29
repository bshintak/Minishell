/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:25:05 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/09 12:29:21 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*ptr;
// 	int		i;
// 	int		j;

// 	if (!s1 || !s2)
// 		return (0);
// 	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!ptr)
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 		ptr[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 		ptr[j++] = s2[i++];
// 	ptr[j] = '\0';
// 	return (ptr);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*snew;
	size_t	n1;
	size_t	n2;
	size_t	slen;

	if (!s1 || !s2)
		return (NULL);
	slen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	snew = (char *)malloc(sizeof(char) * (slen + 1));
	n1 = 0;
	n2 = 0;
	if (snew == NULL)
		return (NULL);
	while (s1[n1] != '\0')
	{
		snew[n1] = s1[n1];
		n1++;
	}
	while (s2[n2] != '\0')
	{
		snew[n1 + n2] = s2[n2];
		n2++;
	}
	snew[n1 + n2] = '\0';
	return (snew);
}
