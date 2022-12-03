#include "../../minishell.h"

void	executor(t_node **tree, char **env)
{
	t_node	*node;

	node = *tree;
	printf("aqui\n");
	if (!node->right)
	{
		if (node->id == ID_BUILTIN)
			find_builtin(node, &env);
	}
	else
	{	
		while (node->right->id == ID_PIPE)
		{
			if (node->left->id == ID_BUILTIN)
				find_builtin(node->left, &env);
			node = node->right;
		}
	}
}