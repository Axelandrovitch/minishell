/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:15:45 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/06 16:14:50 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **copy_env(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	execute_command(t_token *tokens, char **env)
{
	char	**args;
	int		i;

	args = get_args_from_tokens(tokens);
	if (!args || !args[0])
		return ;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], args[0], ft_strlen(args[0])) == 0)
			break ;
		i++;
	}
	if (env[i])
	{
		execve(env[i], args, env);
		perror("execve");
	}
	else
		printf("Command not found: %s\n", args[0]);
	free_vector(args);
}