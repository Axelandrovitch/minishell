/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:43:57 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/05 16:53:03 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_child_process(t_command_block *cmd, int p_fd, int *fd, t_shell *sh)
{
	int	status;

	if (p_fd != -1)
	{
		dup2(p_fd, STDIN_FILENO);
		close(p_fd);
	}
	if (fd != NULL)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	apply_redirections(sh, cmd->redirs);
	if (!cmd->argv || !cmd->argv[0])
		exit_shell(sh, 1);
	if (is_builtin(cmd->argv[0]))
	{
		status = execute_builtin(cmd->argv, sh);
		exit_shell(sh, status);
	}
	execute_external_command(cmd->argv, sh);
}

void	execute_single_builtin(t_command_block *cmd, t_shell *shell)
{
	int	stdin_copy;
	int	stdout_copy;
	int	status;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (stdin_copy == -1 || stdout_copy == -1)
	{
		write(STDERR_FILENO, "dup error\n", 10);
		exit_shell(shell, EXIT_FAILURE);
	}
	apply_redirections(shell, cmd->redirs);
	if (!ft_strcmp(cmd->argv[0], "exit"))
	{
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdin_copy);
		close(stdout_copy);
	}
	status = execute_builtin(cmd->argv, shell);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	shell->last_exit_status = status;
}

pid_t	launch_child(t_command_block *cmd, int prev_fd, int *fd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		exec_child_process(cmd, prev_fd, fd, shell);
	}
	return (pid);
}

int	pipe_and_execute(t_command_block *cmd, int prev_fd, int *fd, t_shell *shell)
{
	if (cmd->next)
	{
		if (prepare_pipe(fd) == -1)
			return (-1);
		return (launch_child(cmd, prev_fd, fd, shell));
	}
	return (launch_child(cmd, prev_fd, NULL, shell));
}
