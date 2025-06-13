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

static void	heredoc_child(t_redir *r, int w_fd, t_token *operand, t_shell *sh)
{
	char	*line;
	int		expand;

	expand = operand->type != T_SQUOTE && operand->type != T_DQUOTE;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, operand->value) == 0)
		{
			free(line);
			break ;
		}
		write_line_to_fd(w_fd, line, expand, sh);
		free(line);
	}
	close(w_fd);
	clean_other_redirs(sh->command_blocks, r);
	exit_shell(sh, 0);
}

static int	heredoc_parent(pid_t pid, int *pipe_fd, t_shell *shell)
{
	int	status;

	close(pipe_fd[1]);
	wait_and_get_status(pid, &status);
	if (status == 130 || status == 128 + SIGINT)
	{
		close(pipe_fd[0]);
		shell->last_exit_status = status;
		return (-1);
	}
	return (pipe_fd[0]);
}

int	handle_heredoc(t_redir *redir, t_token *operand, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_child(redir, pipe_fd[1], operand, shell);
	}
	else if (pid > 0)
		return (heredoc_parent(pid, pipe_fd, shell));
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (-1);
}

int	prepare_heredocs(t_command_block *cmd, t_shell *shell)
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
				fd = handle_heredoc(redir, redir->operand, shell);
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
