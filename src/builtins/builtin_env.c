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

int	builtin_env(char **args, char **env)
{
	int	i;
	
	if (args[1])
	{
		printf("env: too many arguments\n");
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
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