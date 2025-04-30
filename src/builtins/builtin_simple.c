/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:32:27 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:16:45 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

static int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

static int	builtin_exit(char **args)
{
	int	exit_code;

	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
			exit_code = 255;
	}
	else
		exit_code = 0;
	printf("exit\n");
	exit(exit_code);
}

int	execute_builtin(t_token *tokens)
{
	char **args;

	if (!tokens)
		return (1);
	args = get_args_from_tokens(tokens);
	if (!args || !args[0])
		return (free_vector(args), 1);

	if (strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	else if (strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else
	{
		free_vector(args);
		return (1);
	}
	free_vector(args);
	return (0);
}
