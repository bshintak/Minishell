#include "../../minishell.h"

void	execute_cmd(t_node *tree, char ***env)
{
	char	**cmd;
	int		i;

	(void)env;
	cmd = ((char **)(tree->data));
	i = 0;
	while (cmd[i])
	{
		printf("Cmd[%d] is: %s\n", i, cmd[i]);
		i++;
	}
}

void	executor(t_node **tree, char ***env)
{
	t_node	*node;

	node = *tree;
	if (!node->right)
	{
		if (node->id == ID_BUILTIN)
			find_builtin(node, env);
		if (node->id == ID_COMMAND)
			execute_cmd(node, env);

	}
	else
	{	
		while (node->right->id == ID_PIPE)
		{
			if (node->left->id == ID_BUILTIN)
				find_builtin(node->left, env);
			if (node->left->id == ID_COMMAND)
				execute_cmd(node->left, env);
			node = node->right;
		}
		if (node->left->id == ID_BUILTIN)
			find_builtin(node->left, env);
		else if (node->left->id == ID_COMMAND)
			execute_cmd(node->left, env);
		if (node->right->id == ID_BUILTIN)
			find_builtin(node->right, env);
		else if (node->right->id == ID_COMMAND)
			execute_cmd(node->right, env);
	}
}