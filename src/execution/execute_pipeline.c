/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:46:01 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/03 13:50:34 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_all_processes(pid_t *pids, int count, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < count)
	{
		wait_and_get_status(pids[i], &shell->last_exit_status);
		i = i + 1;
	}
}

void	execute_commands(t_command_block *cmd, int prev_fd, t_shell *shell)
{
	pid_t			pids[1024];
	int				i;
	int				fd[2];
	t_command_block	*current;

	current = cmd;
	i = 0;
	while (current)
	{
		pids[i] = pipe_and_execute(current, prev_fd, fd, shell);
		if (pids[i] == -1)
			return ;
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i = i + 1;
		current = current->next;
	}
	wait_all_processes(pids, i, shell);
}

void	execute_pipeline(t_shell *shell)
{
	t_command_block	*cmd;
	int				prev_fd;

	cmd = shell->command_blocks;
	prev_fd = -1;
	if (is_single_builtin(cmd))
	{
		execute_single_builtin(cmd, shell);
		return ;
	}
	execute_commands(cmd, prev_fd, shell);
}
