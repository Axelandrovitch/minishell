/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:46:01 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/29 18:00:06 by dcampas-         ###   ########.fr       */
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

int	prepare_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	update_parent_state(pid_t pid, int *fd, int *prev_fd, bool has_next, t_shell *shell)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	wait_and_get_status(pid, &shell->last_exit_status);
}

void	exec_external_command(char **argv, t_shell *shell)
{
	char	*path;

	path = NULL;
	if (ft_strchr(argv[0], '/') != NULL)
		path = ft_strdup(argv[0]);
	else
		path = get_pathname(argv[0], shell->bin_paths);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(argv[0], STDERR_FILENO);
		exit_shell(shell, 127);
	}
	execve(path, argv, shell->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	execute_child_process(t_command_block *cmd, int prev_fd, int *fd, t_shell *shell)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (fd != NULL)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	apply_redirections(cmd->redirs, shell);
	if (!cmd->argv || !cmd->argv[0])
		exit(1);
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin(cmd->argv, shell);
		exit(0);
	}
	exec_external_command(cmd->argv, shell);
}


void	execute_single_builtin(t_command_block *cmd, t_shell *shell)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	apply_redirections(cmd->redirs, shell);
	execute_builtin(cmd->argv, shell);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
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

void	execute_child_wrapper(t_command_block *cmd, int prev_fd, int *fd, t_shell *shell)
{
	setup_child_signals();
	if (cmd->next != NULL)
		execute_child_process(cmd, prev_fd, fd, shell);
	else
		execute_child_process(cmd, prev_fd, NULL, shell);
}

void	update_parent_wrapper(pid_t pid, int *fd, int *prev_fd, t_command_block *next, t_shell *shell)
{
	if (next != NULL)
		update_parent_state(pid, fd, prev_fd, 1, shell);
	else
		update_parent_state(pid, NULL, prev_fd, 0, shell);
}

void	exec_commands(t_command_block *cmd, int prev_fd, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	while (cmd)
	{
		if (cmd->next)
		{
			if (prepare_pipe(fd) == -1)
				return ;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
			execute_child_wrapper(cmd, prev_fd, fd, shell);
		else
			update_parent_wrapper(pid, fd, &prev_fd, cmd->next, shell);
		cmd = cmd->next;
	}
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
	exec_commands(cmd, prev_fd, shell);
}
