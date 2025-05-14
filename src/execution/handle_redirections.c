/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:57:42 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/14 15:18:39 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

static int	is_redirection(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_APPEND 
			|| token->type == T_REDIR_OUT || token->type == T_HEREDOC)
		return (1);
	return (0);
}

static int	handle_fd(enum e_token_type type, char *filename)
{
	int	fd;

	fd = -1;
	printf("DEBUG: handle_fd() called with type = %d, filename = %s\n", type, filename);
	if (type == T_REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == T_REDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == T_REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == T_HEREDOC)
	{
		printf("Heredoc TODO\n");
		exit(0);
	}
	printf(" fd value before return in handle_fd: %d\n", fd);
	return (fd);
}

int	handle_redirections(t_command_block *command_block)
{
	t_token	*token;
	t_token	*file_token;
	int		fd;

	token = command_block->tokens;
	fd = -1;
	while (token)
	{
		if (is_redirection(token))
		{
			file_token = token->next;
			if (!file_token)
			{
				ft_putstr_fd("minishell: syntax error near `newline`\n",STDERR_FILENO);
				return (1);
			}
			if (file_token->type != T_WORD)
			{
				ft_putstr_fd("minishell: syntax error near `", 2);
				ft_putstr_fd(file_token->value, 2);
				ft_putstr_fd("`\n", 2);
				return (1);
			}
			fd = handle_fd(token->type, file_token->value);
			if (fd == -1)
			{
				perror("open");
				printf("DEBUG PRINT: Remember to clean before exit\n");
				exit(1);
			}
			if (token->type == T_REDIR_OUT || token->type == T_REDIR_APPEND)
				dup2(fd, STDOUT_FILENO);
			else if (token->type == T_REDIR_IN || token->type == T_HEREDOC)
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		token = token->next;
	}
	return (0);
}
