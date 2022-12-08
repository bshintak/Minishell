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
    size = size_parser(token);
    while (env[i] && ft_strncmp(env[i], token, size))
		i++;
    if (env[i])
        return (env[i] + size + 1);
    return (NULL);
}

char    *join_exp(char *token, char *new_token)
{
    char    *ret;

    ret = NULL;
    if (token && new_token)
        ret = ft_strjoin(token, new_token);
    free(token);
    return (ret);
}

char    *join_tokens(char *token, char *new_token)
{
    char    *ret;

    ret = NULL;
    if (token && new_token)
        ret = ft_strjoin(token, new_token);
    free(token);
    free(new_token);
    return (ret);
}

char	*join_char(char *token, char c)
{
	char	*ret;
	char	aux[2];

	if (!token)
		return (0);
	aux[0] = c;
	aux[1] = '\0';
	ret = ft_strjoin(token, aux);
	free(token);
	return (ret);
}

int	word_size_parser(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '$')
			return (i);
	}
	return (i);
}

int	is_permited_char_env_name(char c, int i)
{
	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	else if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	else
		return (0);
}

int	size_env(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_permited_char_env_name(str[i], i))
			return (i);
	}
	return (i);
}

int	size_parser(char *s)
{
    int	i;

    i = -1;
	if (ft_strchr("\'\"", s[0]))
	{
	    i = 0;
	    while (s[++i])
	    {
	    	if (s[i] == s[0])
	    		return (i + 1);
	    }
	    return (0);
    }
	else
	{
        while (s[++i])
	    {
	    	if (s[i] == '\'' || s[i] == '\"')
	    		return (i);
	    }
	    return (i);
    }
    return (0);
}