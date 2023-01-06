/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:11:34 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/06 18:12:58 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_status(int val2)
{
	if (WIFSIGNALED(val2))
	{
		(*exit_status()).i = WTERMSIG(val2) + 128;
		if ((*exit_status()).i == 130)
			write(1, "\n", 1);
	}
	else
		(*exit_status()).i = WEXITSTATUS(val2);
}

void	error_readline_her(char *str, char *eof, int exit_stat)
{
	if (!str)
	{
		ft_putstr_fd("\nshell: warning: here-document delimited ", 1);
		ft_putstr_fd("by end-of-file (wanted `", 1);
		write(1, eof, ft_strlen(eof) - 1);
		ft_putstr_fd("')\n", 1);
		free(eof);
		free(str);
		exit(exit_stat);
	}
	free (eof);
}

int	wait_heredoc(t_node **tree, t_pipex *e)
{
	int	stat;

	close(((*tree)->p)[1]);
	waitpid(e->pid, &stat, 0);
	update_status(stat);
	if ((*exit_status()).i == 129 || (*exit_status()).i == 130)
	{
		if ((*exit_status()).i == 129)
			(*exit_status()).i = 0;
		return (1);
	}
	return (0);
}

void	new_line_exist(char *new_line, int fd, char **env)
{
	char	*join;
	char	*parser;

	join = ft_strjoin(new_line, "\n");
	free (new_line);
	parser = word_parser(join, env, REDIR);
	write(fd, parser, ft_strlen(parser));
	free(join);
}
