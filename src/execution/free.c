/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:50:09 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/20 18:52:59 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->filename)
			free(redirs->filename);
		free(redirs);
		redirs = tmp;
	}
}

void	free_command_blocks(t_command_block *command_blocks)
{
	t_command_block	*tmp;

	while (command_blocks)
	{
		tmp = command_blocks->next;
		free_tokens(command_blocks->tokens);
		free_tokens(command_blocks->argv_tokens);
		free_redirs(command_blocks->redirs);
		free(command_blocks);
		command_blocks = tmp;
	}
}

void	free_shell(t_shell	*shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->expanded)
	{
		free(shell->expanded);
		shell->expanded = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->command_blocks)
	{
		free_command_blocks(shell->command_blocks);
		shell->command_blocks = NULL;
	}
}

void	free_env(t_shell *shell)
{
	free_vector(shell->env);
	free_vector(shell->bin_paths);
}

void	exit_shell(t_shell	*shell, int exit_code)
{
	free_shell(shell);
	free_env(shell);
	rl_clear_history();
	exit(exit_code);
}
