/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:17:35 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 11:17:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (1);
	if (!argv[0])
		return (printf("Error: No command provided\n"), free_vector(argv), 1);
	if (strcmp(argv[0], "pwd") == 0)
		builtin_pwd(argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		builtin_echo(argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
		builtin_exit(argv, shell);
	else if (ft_strcmp(argv[0], "env") == 0)
		builtin_env(argv, shell->env);
	else if (ft_strcmp(argv[0], "export") == 0)
		builtin_export(argv, shell);
	else if (ft_strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, shell->env);
	else if (ft_strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, shell);
	/*else
	{
		free_vector(argv);
		return (1);
	}
	free_vector(argv);*/
	return (1);
}
