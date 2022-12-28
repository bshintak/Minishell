
#include "../../minishell.h"

void	num_redir(t_pipex *pp, t_node *node)
{
	pp->in = 0;
	pp->out = 0;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_INPUT_REDIR || node->id == ID_INPUT_HERDOC)
			pp->in++;
		else if (node->id == ID_OUTPUT_REDIR || node->id == ID_OUTPUT_APPEND)
			pp->out++;
	}
	printf("in = %d\n", pp->in);
	printf("out = %d\n", pp->out);
}

void	redir_out(t_pipex *pp, t_node *node)
{
	int	out;
	int	fd;

	out = pp->out + 1;
	while (node->left)
	{
		node = node->left;
		if (node->id == ID_OUTPUT_REDIR)
		{
			fd = open(node->data, O_CREAT | O_WRONLY | O_TRUNC, 0644); // O_TRUNC erase and write
			out--; // owner can read and write, cant exec // group and others can just read
		}
		else if (node->id == ID_OUTPUT_APPEND)
		{
			fd = open(node->data, O_CREAT | O_WRONLY | O_APPEND, 0644); // O_APPEND just write
			out--;
		}
		if (fd == -1)
		{
			ft_putstr_fd("Error: couldn't open file: ", STDERR_FILENO);
			ft_putendl_fd(branch->token, STDERR_FILENO);
			exit(1);
		}
		if (out == pp->out)
			dup2(fd, STDOUT_FILENO);
		else
			close(fd);
	}
}

void	redir(t_pipex *pp, t_node *node)
{
	num_redir(pp, node);
	// if (pp->in)
	// 	redir_in();
	// else
	dup2(pp->fd, STDIN_FILENO);
	if (pp->out)
	{
		close(node->p[1]);
		redir_out(pp, node);
	}
	else
	{
		if (pp->num_pipe > 1)
		{
			dup2(node->p[1], STDOUT_FILENO);
			close(node->p[1]);
		}
		else
			close(node->p[1]);
	}
}