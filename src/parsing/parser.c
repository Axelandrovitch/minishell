/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:15:38 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/06 15:15:39 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*append_token_to_command_block(t_token **block_head, t_token *to_add)
{
	t_token	*new_tok;
	t_token	*temp_tok;

	new_tok = malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->type =to_add->type;
	new_tok->value = ft_strdup(to_add->value);
	new_tok->next = NULL;
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

t_command_block	*set_command_block(t_token *head_token)
{
	t_command_block	*command_block;
	t_token	*command_block_tokens;
	t_token	*current_token;

	if (!head_token)
		return (NULL);
	command_block = malloc(sizeof(t_command_block));
	if (!command_block)
		return (NULL);
	current_token = head_token;
	while (current_token && current_token->type != T_PIPE)
	{
		if (!append_token_to_command_block(&command_block_tokens, current_token))
			return (NULL);
		current_token = current_token->next;
	}
	command_block->tokens = command_block_tokens;
	command_block->next = NULL;
	return (command_block);
}

t_command_block	*parse_pipeline(t_token *tokens)
{
	t_command_block *head;
	t_command_block *tail;
	t_command_block *current_block;
	t_token *current_token;

	current_token = tokens;
	while (current_token)
	{
		current_block = set_command_block(current_token);
		if (!current_block)
			return (NULL);
		if (!head)
			head = current_block;
		else
			tail->next = current_block;
		tail = current_block;
		while (current_token && current_token->type != T_PIPE)
			current_token = current_token->next;
		if (current_token && current_token->type == T_PIPE)
			current_token = current_token->next;
	}
	return (head);
}
