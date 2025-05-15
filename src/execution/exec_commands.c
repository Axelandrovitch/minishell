/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahetru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:46:01 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/14 12:50:03 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int prepare_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	execute_child(t_command_block *block, int prev_fd, int *fd, t_shell *shell)
{
	char	**args;
	char	*pathname;

	args = get_args_from_tokens(block->tokens);
	if (!args)
		exit(1);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (fd)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (ft_strchr(args[0], '/'))
		pathname = ft_strdup(args[0]);
	else
		pathname = get_pathname(args[0], shell->bin_paths);
	if (!pathname)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(args[0], STDERR_FILENO);
		free_vector(args);
		exit(127);
	}
	execve(pathname, args, shell->env);
	perror("execve");
	free_vector(args);
	exit(EXIT_FAILURE);
}

void execute_parent(pid_t pid, int *fd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (fd)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	waitpid(pid, NULL, 0);
}

void	execute_pipeline(t_shell *shell)
{
	t_command_block *current = shell->command_blocks;
	int fd[2];
	int prev_fd = -1;
	pid_t pid;

	while (current)
	{
		if (current->next && prepare_pipe(fd) == -1)
			return;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}
		else if (pid == 0)
		{
			handle_redirections(current);
			if (current->next)
				execute_child(current, prev_fd, fd, shell);
			else
				execute_child(current, prev_fd, NULL, shell);
		}
		else
		{
			if (current->next)
				execute_parent(pid, fd, &prev_fd);
			else
				execute_parent(pid, NULL, &prev_fd);
		}
		current = current->next;
	}
}

