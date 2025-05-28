/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:16 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/22 16:39:40 by dcampas-         ###   ########.fr       */
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
	char	**sorted_env;

	sorted_env = copy_environment(env);
	if (!sorted_env)
		return (1);
	sort_env_copy(sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	free_vector(sorted_env);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	int		i;
	int		eq_pos;
	char	*key;
	char	*value;

	if (!args[1])
		return (print_sorted_env(shell->env));
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
			if (!key)
				return (1);
			if (args[i][eq_pos] == '=')
				value = ft_strdup(args[i] + eq_pos + 1);
			else
				value = NULL;
			if (value == NULL && args[i][eq_pos] == '=')
				return (1);
			add_or_update_env(&shell->env, key, value);
			{
				free(key);
				free(value);
				return (1);
			}
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
