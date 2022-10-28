/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:11:37 by bshintak          #+#    #+#             */
/*   Updated: 2022/10/28 18:36:54 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is(char c, char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0' && c != set[i])
		i++;
	if (c == set[i])
		return (1);
	return (0);
}

// void	token_list(char *line, t_list **idk)
// {
// 	int	i;
// 	t_token *token;
// 	char	*ptr;

// 	i = 0;
// 	while (token)
// 	{
// 		ptr = get_token(line, &i);
// 		if (ptr)
// 		{
// 			token = malloc(sizeof(t_token));
// 			if (!token)
// 				return ;
// 			token->content = ptr;
// 			ft_lstadd_back(idk, ft_lstnew(token));
// 		}
// 		else
// 			return ;
// 	}
// }

void	get_id(char *word)
{
	t_token	*wtv;
	if (word[0] == '>' || word[0] == '<')
		wtv->id = ID_REDIR;
	else if (word[0] == '|')
		wtv->id = ID_PIPE;
	else
		wtv->id = ID_WORD;
}

void	parser(char *line)
{
	char	*token;

	token = NULL;
	while (1)
	{
		token = get_token1(line);
		if (!token)
			break ;
		//printf("token = %s\n", token);
		printf("%s ", token);
	}
	printf("\n");
}

char	*get_token(char *line)
{
    t_token *token;
    static int     	i;

    token = malloc(sizeof(t_token));
	token->start = 0;
	printf("aqui\n");
    while (line[i])
    {

		// funcaos retornao substring, recebem index por ponteiro para atualizar o novo endereco
		// se ! spaces <>| chama funcao para ir buscar word
		// else se for operador chama funcao vais buscar operador
		// se for espaco continua nao liga ao espaco
		

		
		if (ft_is(line[i], OPERATORS))
		{
			token->content = ft_substr(line, token->start, i - token->start);
			token->start = i + 1;
			// token->id = ID_REDIR;
			// return (token->content);
		}
        else if (!(ft_is(line[i], SPACES)))
        {
        	token->content = ft_substr(line, token->start, i - token->start);
            token->start = i + 1;
			// token->id = ID_WORD;
			// return(token->content);
        }
        i++;
		if (token->content)
			return(token->content);
    }
	return(NULL);
}

char *get_word(int *i, char *line)
{
	int	final;
	char *word;

	final = *i;
	while (!ft_is(line[final], SPACES_OPERATORS))
		final++;
	// printf("final - i = %d\n", final - *i);
	// printf("i = %d\n", *i);
	// printf("final = %d\n", final);
	word = ft_substr(line, *i, final - *i);
	*i = final;
	//printf("word = %s\n", word);
	return (word);
}

char	*get_operator(int *i, char *line)
{
	char	*redir;

	if ((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '>' && line[*i + 1] == '>'))
	{
		redir = ft_substr(line, *i, 2);
		*i += 1;
	}
	else
		redir = ft_substr(line, *i, 1);
	(*i)++;
	//printf("redir = %s\n", redir);
	return (redir);
	//if ((line[*i] == '<' || line[*i] == '>') && line[*i + 1] != )
	//	redir	
}

char	*get_token1(char *line)
{
    static int     	i = 0;

	// printf("aqui\n");
	// printf("i = %d\n", i);
    while (line[i])
    {
		// printf("whileeeeeeeeee\n");
		if (!ft_is(line[i], SPACES_OPERATORS))
			return (get_word(&i, line));
		if (ft_is(line[i], OPERATORS))
			return (get_operator(&i, line));
        i++;
    }
	return(NULL);
}



// char	*get_token(char *line, int *i)
// {
//     int start;
// 	char *word;
// 	t_token	*wtv;

// 	word = NULL;
// 	start = *i;
//     while (line[*i])
//     {
// 		// ignore spaces
// 		while (line[*i] && ft_is(line[*i], SPACES))
// 			(*i)++;
// 		// set start to first letter
// 		start = *i;
// 		while (line[*i] && !ft_is(line[*i], SPACES))
// 			(*i)++;
// 		if (start != *i)
// 		{
// 			word = ft_substr(line, start, *i - start);
// 			printf("{%d, %d} : %s\n", start, *i, word);
// 		}
// 		// get word
// 		if (word)
// 		{
// 			// get_id(word);
// 			// printf("id = %d\n", wtv->id);
// 			return(word);
// 		}
// 		// update i
//     }
// 	return(NULL);
// }                                                                                                                                                                                                                                                                               
