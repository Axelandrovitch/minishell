/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:20:14 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 12:14:40 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	write_line_to_fd(int fd, char *line, int expand, t_shell *shell)
{
	char	*expanded_line;

	if (expand)
	{
		expanded_line = expand_variables(line, shell);
		if (expanded_line)
		{
			write(fd, expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	handle_heredoc(t_token *operand, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		expand;

	if (pipe(pipe_fd) < 0)
		return (-1);
	expand = operand->type == !T_SQUOTE && operand->type != T_DQUOTE;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);

		while (1)
		{
			char *line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, operand->value) == 0)
			{
				free(line);
				break;
			}
			write_line_to_fd(pipe_fd[1], line, expand, shell);
			free(line);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			close(pipe_fd[0]);
			return (-1);
		}
		return pipe_fd[0];
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
}

int prepare_heredocs(t_command_block *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		fd;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				fd = handle_heredoc(redir->operand, shell);
				if (fd < 0)
					return (-1);
				redir->heredoc_fd = fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

