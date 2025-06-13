/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                +#+#+#+#+#+   +#+           */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:57:42 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/11 17:59:37 by ahetru           ###   ########.fr       */
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

static int	handle_fd(t_shell *shell, t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == T_REDIR_OUT)
		fd = open(redir->operand->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_REDIR_APPEND)
		fd = open(redir->operand->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == T_REDIR_IN)
		fd = open(redir->operand->value, O_RDONLY);
	else if (redir->type == T_HEREDOC)
	{
		fd = redir->heredoc_fd;
	}
	if (fd < 0)
	{
		perror("open");
		exit_shell(shell, 1);
	}
	return (fd);
}

void	apply_redirections(t_shell *shell, t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = handle_fd(shell, redir);
		if (fd == -1)
			return ;
		if (redir->type == T_REDIR_OUT || redir->type == T_REDIR_APPEND)
			dup2 (fd, STDOUT_FILENO);
		else if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
			dup2 (fd, STDIN_FILENO);
		if (redir->type == T_HEREDOC)
			redir->heredoc_fd = -1;
		close(fd);
		redir = redir->next;
	}
}
