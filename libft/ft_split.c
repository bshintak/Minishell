/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:07:07 by lleiria-          #+#    #+#             */
/*   Updated: 2022/12/08 11:28:13 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cword(char const *s, char c)
{
	int	n1;
	int	count;

	n1 = 0;
	count = 0;
	while (s[n1])
	{
		while (s[n1] == c)
			n1++;
		if (s[n1] != '\0')
			count++;
		while (s[n1] && (s[n1] != c))
			n1++;
	}
	return (count);
}

static char	*ft_worddup(const char *s, int start, int end)
{
	char	*word;
	int		n2;

	n2 = 0;
	word = (char *)malloc(sizeof(char) * end - start + 1);
	if (word == NULL)
		return (NULL);
	while (start < end)
	{
		word[n2] = s[start];
		n2++;
		start++;
	}
	word[n2] = '\0';
	return (word);
}

char	**ft_spliter(char **split, char *s, char c)
{
	int	n3;
	int	n4;
	int	start;

	n3 = 0;
	n4 = 0;
	start = -1;
	while (n3 <= ft_strlen(s))
	{
		if (s[n3] != c && start < 0)
			start = n3;
		else if ((s[n3] == c || n3 == ft_strlen(s)) && start >= 0)
		{
			split[n4++] = ft_worddup(s, start, n3);
			start = -1;
		}
		n3++;
	}
	split[n4] = 0;
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	char	**split2;

	if (!s)
		return (0);
	split = malloc((ft_cword(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	split2 = ft_spliter(split, s, c);
	return (split2);
}
