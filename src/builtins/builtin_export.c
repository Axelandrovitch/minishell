/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:16 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/13 18:44:13 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_invalid(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	print_sorted_env(char **env)
{
	int		i;
	int		j;
	char	*temp;
	
	i = 0;
	while (env[i] && env[i + 1])
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
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

static int	add_or_update_env(char **env, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_var;
	
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && 
			(env[i][key_len] == '=' || env[i][key_len] == '\0'))
		{
			if (value)
			{
				new_var = ft_strjoin(key, "=");
				free(env[i]);
				env[i] = ft_strjoin(new_var, value);
				free(new_var);
			}
			return (0);
		}
		i++;
	}
	if (value)
	{
		new_var = ft_strjoin(key, "=");
		env[i] = ft_strjoin(new_var, value);
		free(new_var);
	}
	else
		env[i] = ft_strdup(key);
	env[i + 1] = NULL;
	return (0);
}

int	builtin_export(char **args, char **env)
{
	int		i;
	int		eq_pos;
	char	*key;
	char	*value;

	if (!args[1])
		return (print_sorted_env(env));
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			print_invalid(args[i]);
		else
		{
			eq_pos = 0;
			while (args[i][eq_pos] && args[i][eq_pos] != '=')
				eq_pos++;
			key = ft_substr(args[i], 0, eq_pos);
			if (args[i][eq_pos] == '=')
				value = ft_strdup(args[i] + eq_pos + 1);
			else
				value = NULL;
			add_or_update_env(env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}