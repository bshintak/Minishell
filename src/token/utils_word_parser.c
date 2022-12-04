#include "../../minishell.h"

char	*find_shlvl(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6))
		i++;
	if (env[i])
		return (env[i] + 6);
	return (NULL);
}

char    *expand_dollar(char *token, char **env)
{
    int i;
    int size;

    i = 0;
    if (!token)
        return (NULL);
    size = ft_strlen(token);
    while (env[i] && ft_strncmp(env[i], token, size))
        i++;
    if (env[i])
        return (env[i] + size + 1);
    return (NULL);
}