/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:42:06 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/23 12:43:25 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Cuenta el número de variables de entorno en el vector env
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

// Actualiza el valor de una variable de entorno existente
// Se usa en el export y cd
int	update_env_var(char **env, char *var_name, char *value)
{
	char	*env_var;
	char	*temp;
	int		i;
	int		var_len;

	var_len = ft_strlen(var_name);
	if (value)
	{
		temp = ft_strjoin(var_name, "=");
		if (!temp)
			return (1);
		env_var = ft_strjoin(temp, value);
		free(temp);
	}
	else
		env_var = ft_strdup(var_name);
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

// Añade una nueva variable de entorno al vector env

int	add_env_var(char ***env, char *key, char *value)
{
	int		size;
	char	*new_var;
	char	**new_env;
	int		i;

	size = count_environment_vars(*env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	if (value)
	{
		new_var = ft_strjoin(key, "=");
		if (!new_var)
		{
			free(new_env);
			return (1);
		}
		new_env[i] = ft_strjoin(new_var, value);
		free(new_var);
	}
	else
		new_env[i] = ft_strdup(key);
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

// Añade o actualiza una variable de entorno en el vector env
int	add_or_update_env(char ***env, char *key, char *value)
{
	int	pos;

	if (!key || !env || !*env)
		return (1);
	pos = find_env_var(*env, key);
	if (pos >= 0)
		return (update_env_var(*env, key, value));
	else
		return (add_env_var(env, key, value));
}

// Ordena el vector de variables de entorno alfabéticamente
void	sort_env_copy(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}