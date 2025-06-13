/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:41:00 by ahetru            #+#    #+#             */
/*   Updated: 2025/06/10 16:08:34 by ahetru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	form_bin_path(t_shell *shell, char **envp_vec)
{
	char	*full_path;
	int		i;

	i = 0;
	while (envp_vec[i])
	{
		full_path = ft_strjoin(envp_vec[i], "/");
		if (!full_path)
		{
			free_vector(envp_vec);
			perror("Could not create executable path");
			exit_shell(shell, EXIT_FAILURE);
		}
		free(envp_vec[i]);
		envp_vec[i] = full_path;
		i++;
	}
}

char	**set_path_environment(t_shell *shell)
{
	char	*envp;
	char	**envp_vec;

	envp = ft_getenv(shell, "PATH");
	if (!envp)
	{
		return (NULL);
	}
	envp_vec = ft_split(envp, ':');
	if (!envp_vec)
		exit_shell(shell, 1);
	free(envp);
	form_bin_path(shell, envp_vec);
	return (envp_vec);
}

char	*get_pathname(char *command, char **path_variable)
{
	size_t	i;
	int		fd;
	char	*pathname;

	i = 0;
	fd = 0;
	pathname = NULL;
	if (!path_variable || !command)
		exit(1);
	while (path_variable[i])
	{
		pathname = ft_strjoin(path_variable[i], command);
		if (!pathname)
			exit(EXIT_FAILURE);
		if (access(pathname, X_OK) == 0)
			return (pathname);
		free(pathname);
		i++;
	}
	return (NULL);
}

int	count_environment_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

char	**copy_environment(char **envp)
{
	int		i;
	int		len;
	char	**env;
	char	*current_var;

	i = 0;
	len = count_environment_vars(envp);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	while (envp[i] != NULL)
	{
		current_var = strdup(envp[i]);
		if (!current_var)
			return (NULL);
		env[i] = current_var;
		i++;
	}
	env[i] = NULL;
	return (env);
}
