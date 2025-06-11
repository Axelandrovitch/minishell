/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:17:35 by marvin            #+#    #+#             */
/*   Updated: 2025/05/30 17:56:06 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

static void	print_no_command(void)
{
	write(STDERR_FILENO, "Error: No command provided\n", 27);
}

int	execute_builtin(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (1);
	if (!argv[0])
		return (print_no_command(), free_vector(argv), 1);
	if (strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argv, shell));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv, shell));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, shell));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv, shell));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, shell));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, shell));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, shell));
	return (1);
}
