/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:46:24 by bshintak          #+#    #+#             */
/*   Updated: 2022/12/16 18:57:28 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ret_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ret_without_error(char *str)
{
	ft_putstr_fd(str, STDIN_FILENO);
	exit(EXIT_SUCCESS);
}

void	print_error(char *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	print_error2(char *token, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	if (status == MISSING_QUOTE)
		ft_putendl_fd(": missing quotes", STDERR_FILENO);
	else
		ft_putendl_fd(": something wrong", STDERR_FILENO);
}
