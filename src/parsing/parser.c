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

t_token	*token_dup_and_add_back(t_token **block_head, t_token *to_add)
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


t_token	*token_add_back(t_token **block_head, t_token *to_add)
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

t_redir	*redir_add_back(t_redir	**head, enum e_token_type type, const char *filename)
{
	t_redir	*current;
	t_redir	*to_add;

	to_add = malloc(sizeof(t_redir));
	if (!to_add)
	{
		printf("TODO: free memory!\n");
		exit(1);
	}
	to_add->type = type;
	to_add->filename = ft_strdup(filename);
	if (!to_add->filename)
	{
		printf("TODO: free memory!\n");
		exit(1);
	}
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
	t_token	*	token;
	t_token	*	next;
	
	token = command_block->tokens;
	command_block->argv_tokens = NULL;
	command_block->redirs= NULL;
	while(token)
	{
		next = token->next;
		if (is_redirection(token) && next && next->type == T_WORD)
		{
			redir_add_back(&command_block->redirs, token->type, next->value);
			token = next->next;
		}
		else
		{
			token_add_back(&command_block->argv_tokens, token);
			token = token->next;
		}
	}
}

t_command_block	*create_command_block(t_token *head_token)
{
	t_command_block	*command_block;
	t_token	*command_block_tokens;
	t_token	*current_token;

	command_block_tokens = NULL;
	if (!head_token)
		return (NULL);
	command_block = malloc(sizeof(t_command_block));
	if (!command_block)
		return (NULL);
	current_token = head_token;
	while (current_token && current_token->type != T_PIPE)
	{
		if (!token_dup_and_add_back(&command_block_tokens, current_token))
			return (NULL);
		current_token = current_token->next;
	}
	command_block->tokens = command_block_tokens;
	command_block->next = NULL;
	return (command_block);
}

t_command_block	*split_tokens_on_pipe(t_token *tokens)
{
	t_command_block *head;
	t_command_block *tail;
	t_command_block *current_block;
	t_token *current_token;

	current_token = tokens;
	head = NULL;
	tail = NULL;
	while (current_token)
	{
		current_block = create_command_block(current_token);
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

void	parse_pipeline(t_shell *shell, t_token *tokens)
{
	t_command_block	*head;
	t_command_block	*current;

	head = split_tokens_on_pipe(tokens);
	current = head;
	while (current)
	{
		parse_command_block(current);
		current = current->next;
	}
	shell->command_blocks = head;
}

void	print_command_block(t_command_block *block)
{
	t_token	*arg;
	t_redir	*redir;

	static int block_num = 1;
	printf("=== Command Block %d ===\n", block_num++);
	
	// Print argv tokens
	printf("ARGV: ");
	arg = block->argv_tokens;
	if (!arg)
		printf("(none)");
	while (arg)
	{
		printf("[%s] ", arg->value);
		arg = arg->next;
	}
	printf("\n");

	// Print redirections
	printf("REDIRS:\n");
	redir = block->redirs;
	if (!redir)
		printf("  (none)\n");
	while (redir)
	{
		const char *type_str = NULL;
		switch (redir->type)
		{
			case T_REDIR_OUT:		type_str = ">"; break;
			case T_REDIR_APPEND:	type_str = ">>"; break;
			case T_REDIR_IN:		type_str = "<"; break;
			case T_HEREDOC:			type_str = "<<"; break;
			default:				type_str = "?"; break;
		}
		printf("  %s %s\n", type_str, redir->filename);
		redir = redir->next;
	}
	printf("\n");
}

void	print_all_command_blocks(t_command_block *head)
{
	while (head)
	{
		print_command_block(head);
		head = head->next;
	}
}

