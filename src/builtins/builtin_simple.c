/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:32:27 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/29 17:55:06 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(char **args)
{
	char	*cwd; 

	if (args[1])
		return (printf("pwd: too many arguments\n"), 1);
	cwd = getcwd(NULL, 0); //Get the current working directory
	if (!cwd)
		return (perror("getcwd"),1);

	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i] && ft_strncmp(args[i], "-n", 2) == 0)
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

int	builtin_exit(char **args)
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


