/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_blocks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:43:58 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 19:43:59 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_dup(t_token	*token)
{
	t_token	*dup;

	dup = malloc(sizeof(t_token));
	if (!dup)
		return (NULL);
	dup->type = token->type;
	dup->value = ft_strdup(token->value);
	if (!dup->value)
	{
		free(dup);
		return (NULL);
	}
	dup->next = NULL;
	return (dup);
}

t_token	*token_dup_and_add_back(t_token **block_head, t_token *to_add)
{
	t_token	*new_tok;
	t_token	*temp_tok;

	new_tok = token_dup(to_add);
	if (!new_tok)
		return (NULL);
	if (*block_head == NULL)
		*block_head = new_tok;
	else
	{
		temp_tok = *block_head;
		while (temp_tok->next)
			temp_tok = temp_tok->next;
		temp_tok->next = new_tok;
	}
	return (new_tok);
}

t_token	*token_add_back(t_token **block_head, t_token *to_add)
{
	t_token	*new_tok;
	t_token	*temp_tok;

	if (!to_add)
		return (NULL);
	new_tok = new_token(to_add->type, to_add->value, ft_strlen(to_add->value));
	if (!new_tok)
		return (NULL);
	if (*block_head == NULL)
		*block_head = new_tok;
	else
	{
		temp_tok = *block_head;
		while (temp_tok->next)
			temp_tok = temp_tok->next;
		temp_tok->next = new_tok;
	}
	return (new_tok);
}

t_redir	*redir_add_back(t_redir	**head, enum e_token_type type
						, t_token *operand)
{
	t_redir	*current;
	t_redir	*to_add;

	to_add = malloc(sizeof(t_redir));
	if (!to_add)
		return (NULL);
	to_add->type = type;
	to_add->heredoc_fd = -1;
	to_add->operand = token_dup(operand);
	if (!to_add->operand)
		return (NULL);
	to_add->next = NULL;
	if (!*head)
		*head = to_add;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
	return (to_add);
}

void	parse_command_block(t_command_block *command_block)
{
	t_token	*token;
	t_token	*next;

	token = command_block->tokens;
	command_block->argv_tokens = NULL;
	command_block->redirs = NULL;
	while (token)
	{
		next = token->next;
		if (is_redirection(token) && next)
		{
			redir_add_back(&command_block->redirs, token->type, next);
			token = next->next;
		}
		else
		{
			token_add_back(&command_block->argv_tokens, token);
			token = token->next;
		}
	}
}
