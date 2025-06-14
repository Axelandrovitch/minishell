/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:19:01 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/13 17:48:19 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_direct_path(char **argv, t_shell *shell)
{
	char	*path;

	path = ft_strdup(argv[0]);
	if (!path)
		exit_shell(shell, 1);
	if (access(path, X_OK) != 0)
	{
		if (errno == ENOENT)
			print_no_such_file_or_directory(argv[0]);
		else if (errno == EACCES)
			print_permission_denied(argv[0]);
		else
			perror("minishell");
		free(path);
		if (errno == EACCES)
			exit_shell(shell, 126);
		else
			exit_shell(shell, 127);
	}
	execve(path, argv, shell->env);
	perror("execve");
	free(path);
	exit_shell(shell, EXIT_FAILURE);
}

static void	handle_path_lookup(char **argv, t_shell *shell)
{
	char	**bin_paths;
	char	*path;

	bin_paths = set_path_environment(shell);
	if (!bin_paths)
	{
		print_no_such_file_or_directory(argv[0]);
		exit_shell(shell, 127);
	}
	path = get_pathname(argv[0], bin_paths);
	if (!path)
	{
		print_command_not_found(argv[0]);
		free_vector(bin_paths);
		exit_shell(shell, 127);
	}
	execve(path, argv, shell->env);
	perror("execve");
	free(path);
	free_vector(bin_paths);
	exit(EXIT_FAILURE);
}

void	execute_external_command(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return ;
	if (ft_strchr(argv[0], '/'))
		handle_direct_path(argv, shell);
	else
		handle_path_lookup(argv, shell);
}
