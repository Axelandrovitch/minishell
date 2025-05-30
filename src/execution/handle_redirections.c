/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:57:42 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/22 14:24:44 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_APPEND
		|| token->type == T_REDIR_OUT || token->type == T_HEREDOC)
		return (1);
	return (0);
}

static int	handle_fd(enum e_token_type type, char *filename, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (type == T_REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == T_REDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == T_REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == T_HEREDOC)
	{
		fd = handle_heredoc(filename, shell);
	}
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

void	apply_redirections(t_redir *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		fd = handle_fd(redir->type, redir->filename, shell);
		if (fd == -1)
		{
			exit(1); // esto se tendria que gestionar en la funcion que da su valor al file descriptor y anadir perror
		}
		if (redir->type == T_REDIR_OUT || redir->type == T_REDIR_APPEND)
			dup2 (fd, STDOUT_FILENO);
		else if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
			dup2 (fd, STDIN_FILENO);
		close(fd);
		redir = redir->next;
	}
}
//
// int	handle_redirections(t_command_block *command_block)
// {
// 	t_token	*token;
// 	t_token	*file_token;
// 	int		fd;
//
// 	token = command_block->tokens;
// 	fd = -1;
// 	while (token)
// 	{
// 		if (is_redirection(token))
// 		{
// 			file_token = token->next;
// 			if (!file_token)
// 			{
// 				ft_putstr_fd ("minishell: syntax error near `newline`\n", STDERR_FILENO);
// 				return (1);
// 			}
// 			if (file_token->type != T_WORD)
// 			{
// 				ft_putstr_fd("minishell: syntax error near `", STDERR_FILENO);
// 				ft_putstr_fd(file_token->value, STDERR_FILENO);
// 				ft_putstr_fd("`\n", STDERR_FILENO);
// 				return (1);
// 			}
// 			fd = handle_fd(token->type, file_token->value);
// 			if (fd == -1)
// 			{
// 				perror("open");
// 				printf("DEBUG PRINT: Remember to clean before exit\n");
// 				exit(1);
// 			}
// 			if (token->type == T_REDIR_OUT || token->type == T_REDIR_APPEND)
// 				dup2(fd, STDOUT_FILENO);
// 			else if (token->type == T_REDIR_IN || token->type == T_HEREDOC)
// 				dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }
