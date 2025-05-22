/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:41:00 by ahetru            #+#    #+#             */
/*   Updated: 2025/05/22 14:24:39 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_vector(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
	{
		printf("%s\n", vec[i]);
		i++;
	}
}

void	free_vector(char **vec)
{
	int	i;

	i = 0;
	if (!vec)
		return ;
	while (vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}

static void	form_bin_path(char **envp_vec)
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
			exit(EXIT_FAILURE);
		}
		free(envp_vec[i]);
		envp_vec[i] = full_path;
		i++;
	}
}

char	**set_path_environment(void)
{
	const char	*envp;
	char		**envp_vec;

	envp = getenv("PATH");
	if (!envp)
	{
		printf("No environment found\n");
		exit(1);
	}
	envp_vec = ft_split(envp + 5, ':');
	if (!envp_vec)
	{
		printf("Memory allocation failed\n");
		exit (1);
	}
	form_bin_path(envp_vec);
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
		fd = access(pathname, X_OK);
		if (fd != -1)
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
		exit(EXIT_FAILURE);
	while (envp[i] != NULL)
	{
		current_var = strdup(envp[i]);
		if (!current_var)
			exit(EXIT_FAILURE);
		env[i] = current_var;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*ft_getenv(t_shell *shell, char *var)
{
	int		i;
	int		var_len;
	char	*ret;

	i = 0;
	var_len = ft_strlen(var);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, var_len) == 0
			&& shell->env[i][var_len] == '=')
		{
			ret = ft_strdup(shell->env[i] + var_len + 1);
			if (!ret)
				exit_shell(shell, 1);
			return (ret);
		}
		i++;
	}
	return (NULL);
}
