/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:26:25 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 11:26:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int	builtin_env(char **args, t_shell *shell)
{
	int	i;

	if (args[1])
	{
		shell->last_exit_status = 1;
		write(STDERR_FILENO, "env: too many arguments\n", 24);
		return (1);
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	shell->last_exit_status = 0;
	return (shell->last_exit_status);
}
