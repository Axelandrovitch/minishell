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

//Env export y unset

int	builtin_env(char **env) // BASH ONLY ACCEPT 1 ARGUMENT 
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s", env[i]);
		i++;	
	}
	return (0);
}

int	builtin_export(char **args, char **env) //COMPORBAR SI ESTA BIEN
{
	int		i;
	char	*equal_sign;

	i = 0;
	if (!args || !args[0])
		return (0);
	if (!args[1])
		return (builtin_env(env));
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (setenv(args[i], equal_sign + 1, 1) == -1)
				return (perror("export"), 1);
		}
		else
		{
			if (getenv(args[i]))
				printf("%s=%s\n", args[i], getenv(args[i]));
		}
		i++;
	}
	return (0);
}

/*
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (builtin_env(envp));
}
*/