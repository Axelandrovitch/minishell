/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:13:49 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/03 16:56:41 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int	builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if (printf("%s", args[i]) == -1)
		{
			shell->last_exit_status = 1;
			return (1);
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->last_exit_status = 0;
	return (shell->last_exit_status);
}
