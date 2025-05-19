/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:28:26 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/19 13:28:27 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int	print_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near `", STDERR_FILENO);
	ft_putstr_fd(token->value, STDERR_FILENO);
	ft_putstr_fd("`\n", STDERR_FILENO);
	return (1);
}

int	pipe_error(t_token *token, int index)
{
	if (token->type == T_PIPE)
	{
		if (index == 0)
			return (1);
		if (!token->next)
			return (1);
		if (token->next->type == T_PIPE)
			return (1);
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*current;
	int		index;

	current = tokens;
	index = 0;
	while (current)
	{
		if (pipe_error(current, index))
			return (print_syntax_error(current));
		index++;
		current = current->next;
	}
	return (0);
}
