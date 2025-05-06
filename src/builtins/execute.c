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

int	execute_builtin(t_token *tokens, char **env)
{
	char **args;

	if (!tokens)
		return (1);
	args = get_args_from_tokens(tokens);
	if (!args || !args[0])
		return (free_vector(args), 1);

	printf("DEBUG: %s\n", tokens[0].value);

	if (!args[0])
		return (printf("Error: No command provided\n"), free_vector(args), 1);
	if (strcmp(args[0], "pwd") == 0)
		builtin_pwd(args);
	else if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(env);
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, env);

	/*else if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args, env);*/
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, env);
	else
	{
		free_vector(args);
		return (1);
	}
	free_vector(args);
	return (0);
}