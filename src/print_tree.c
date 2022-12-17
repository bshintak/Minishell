/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:20:29 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/12 11:23:49 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define COUNT 10

//cat <in >out | ls <in2 >out2 | <<in3 >>out3 grep | <<in4 less >out4

static void	print2dutil(t_node *root, int space);
void		print_node1(t_node *node);


// Code based in https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/


void	print2d(t_node *root)
{
	print2dutil(root, 0);
}

// It does reverse inorder traversal
static void	print2dutil(t_node *root, int space)
{
	if (root == NULL)
		return ;
	// Increase distance between levels
	space += COUNT;
	// Process right child first
	print2dutil(root->right, space);
	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	//printf("%s\n", root->data);
	print_node1(root);
	// Process left child
	print2dutil(root->left, space);
}

void	print_array_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("\n");
}

void	print_data(t_node node)
{
	char	**c;
	// t_redir	*r;

	if (node.id == ID_COMMAND)
	{
		c = (char **)node.data;
		print_array_string(c);
	}
	// else
	// {
	// 	r = (t_redir *) node.data;
	// 	printf("%s\n", r->redir);
	// }
}

void	print_node1(t_node *node)
{
	if (node->id == ID_PIPE)
	{
		printf("|\n");
		//printf("| r: %i w: %i\n", ((t_pipe *) node->data)->r, ((t_pipe *) node->data)->w);
	}
	else
	{
		if (node->id == ID_INPUT_REDIR)
			printf("< ");
		else if (node->id == ID_OUTPUT_REDIR)
			printf("> ");
		else if (node->id == ID_OUTPUT_APPEND)
			printf(">> ");
		else if (node->id == ID_INPUT_HERDOC)
			printf("<< ");
		print_data(*node);
	}
}
