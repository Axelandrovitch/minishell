/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:38:33 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 12:14:36 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(const char *command)
{
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	return (0);
}

bool	is_single_builtin(t_command_block *cmd)
{
	if (cmd == NULL)
		return (false);
	if (cmd->next != NULL)
		return (false);
	if (!cmd->argv || !cmd->argv[0])
		return (false);
	if (!is_builtin(cmd->argv[0]))
		return (false);
	return (true);
}

int	prepare_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	cleanup_all_heredocs(t_command_block *cmd)
{
	t_command_block	*current;
	t_redir			*redir;

	current = cmd;
	while (current)
	{
		redir = current->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->heredoc_fd > 2)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}

void	clean_other_redirs(t_command_block *cmd, t_redir *cur_redir)
{
	t_command_block	*current;
	t_redir			*redir;

	if (!cmd || !cur_redir)
		return ;
	current = cmd;
	while (current)
	{
		redir = current->redirs;
		while (redir)
		{
			if (redir != cur_redir
				&& redir->type == T_HEREDOC
				&& redir->heredoc_fd > 2)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
