/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:16 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/29 17:50:43 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	print_sorted_env(char **env)
{
	char	**sorted_env;
	int		result;

	sorted_env = copy_environment(env);
	if (!sorted_env)
		return (1);
	sort_env_copy(sorted_env);
	result = print_filtered_env(sorted_env);
	free_vector(sorted_env);
	return (result);
}

static int	find_equals_position(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != '=')
		pos++;
	return (pos);
}

static int	extract_key_value(char *arg, char **key, char **value)
{
	int	eq_pos;

	eq_pos = find_equals_position(arg);
	*key = ft_substr(arg, 0, eq_pos);
	if (!*key)
		return (1);
	if (arg[eq_pos] == '=')
	{
		*value = ft_strdup(arg + eq_pos + 1);
		if (!*value)
		{
			free(*key);
			return (1);
		}
	}
	else
		*value = NULL;
	return (0);
}

static int	process_single_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier_export(arg))
	{
		print_invalid_export(arg);
		return (0);
	}
	if (extract_key_value(arg, &key, &value))
		return (1);
	if (add_or_update_env(&shell->env, key, value))
	{
		free(key);
		free(value);
		return (1);
	}
	free(key);
	free(value);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	error;

	if (!args[1])
		return (print_sorted_env(shell->env));
	i = 1;
	error = 0;
	while (args[i])
	{
		if (process_single_arg(args[i], shell))
			error = 1;
		i++;
	}
	return (error);
}
