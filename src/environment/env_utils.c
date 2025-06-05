/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:42:06 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/05 13:19:30 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_env_var(char **env, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, key_len) == 0)
			&& ((env[i][key_len] == '=') || (env[i][key_len] == '\0')))
			return (i);
		i++;
	}
	return (-1);
}

static char	*create_env_string(char *var_name, char *value)
{
	char	*env_var;
	char	*temp;

	if (value)
	{
		temp = ft_strjoin(var_name, "=");
		if (!temp)
			return (NULL);
		env_var = ft_strjoin(temp, value);
		free(temp);
		if (!env_var)
			return (NULL);
	}
	else
		env_var = ft_strdup(var_name);
	return (env_var);
}

int	update_env_var(char **env, char *var_name, char *value)
{
	char	*env_var;
	int		i;
	int		var_len;

	var_len = ft_strlen(var_name);
	env_var = create_env_string(var_name, value);
	if (!env_var)
		return (1);
	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], var_name, var_len) == 0)
			&& ((env[i][var_len] == '=') || (env[i][var_len] == '\0')))
		{
			free(env[i]);
			env[i] = env_var;
			return (0);
		}
		i++;
	}
	free(env_var);
	return (0);
}

static int	setup_new_env(char ***env, char **new_env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	return (i);
}

int	add_env_var(char ***env, char *key, char *value)
{
	int		size;
	char	**new_env;
	int		i;

	size = count_environment_vars(*env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (1);
	i = setup_new_env(env, new_env, size);
	new_env[i] = create_env_string(key, value);
	if (!new_env[i])
	{
		free(new_env);
		return (1);
	}
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}
