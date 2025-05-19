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
#include <string.h>

int	is_builtin(const char *command)
{
	if (strcmp(command, "exit"))
		return (1);
	if (strcmp(command, "echo"))
		return (1);
	if (strcmp(command, "cd"))
		return (1);
	if (strcmp(command, "pwd"))
		return (1);
	if (strcmp(command, "export"))
		return (1);
	if (strcmp(command, "unset"))
		return (1);
	if (strcmp(command, "env"))
		return (1);
	return (0);
}

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

void	exec_child(t_command_block *block, int prev_fd, int *fd, t_shell *shell)
{
	char	*pathname;

    if (!block->argv || !block->argv[0])
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
    apply_redirections(block->redirs);
	if (is_builtin(block->argv[0]))
		execute_builtin(block->argv);
    if (ft_strchr(block->argv[0], '/'))
        pathname = ft_strdup(block->argv[0]);
    else
        pathname = get_pathname(block->argv[0], shell->bin_paths);

    if (!pathname)
    {
        ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
        ft_putendl_fd(block->argv[0], STDERR_FILENO);
		exit_shell(shell, 127);
    }

    execve(pathname, block->argv, shell->env);
    perror("execve");
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

// testeamos con exec_child
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
				exec_child(current, prev_fd, fd, shell);
			else
				exec_child(current, prev_fd, NULL, shell);
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

