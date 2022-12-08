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
