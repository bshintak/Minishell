#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);

	else if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
