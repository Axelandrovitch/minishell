/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:15:38 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 19:43:06 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command_block	*create_command_block(t_token *head_token)
{
	t_command_block	*command_block;
	t_token			*command_block_tokens;
	t_token			*current_token;

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
		{
			free_tokens(command_block_tokens);
			free(command_block);
			return (NULL);
		}
		current_token = current_token->next;
	}
	command_block->tokens = command_block_tokens;
	command_block->next = NULL;
	return (command_block);
}

t_command_block	*split_tokens_on_pipe(t_token *tokens)
{
	t_command_block	*head;
	t_command_block	*tail;
	t_command_block	*current_block;
	t_token			*current_token;

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
		current->argv = get_args_from_tokens(current->argv_tokens);
		current = current->next;
	}
	shell->command_blocks = head;
}

// void	print_command_block(t_command_block *block)
// {
// 	t_token	*arg;
// 	t_redir	*redir;
// 	
// 	static int block_num = 1;
// 	printf("=== Command Block %d ===\n", block_num++);
// 	printf("ARGV: ");
// 	arg = block->argv_tokens;
// 	if (!arg)
// 		printf("(none)");
// 	while (arg)
// 	{
// 		printf("[%s] ", arg->value);
// 		arg = arg->next;
// 	}
// 	printf("\n");
// 	printf("REDIRS:\n");
// 	redir = block->redirs;
// 	if (!redir)
// 		printf("  (none)\n");
// 	while (redir)
// 	{
// 		const char *type_str = NULL;
// 		switch (redir->type)
// 		{
// 			case T_REDIR_OUT:		type_str = ">"; break;
// 			case T_REDIR_APPEND:	type_str = ">>"; break;
// 			case T_REDIR_IN:		type_str = "<"; break;
// 			case T_HEREDOC:			type_str = "<<"; break;
// 			default:				type_str = "?"; break;
// 		}
// 		printf("  %s %s \n", type_str, redir->operand->value);
// 		redir = redir->next;
// 	}
// 	printf("\n");
// }
//
// void	print_all_command_blocks(t_command_block *head)
// {
// 	while (head)
// 	{
// 		print_command_block(head);
// 		head = head->next;
// 	}
// }
//
