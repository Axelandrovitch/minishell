/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:16 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/13 15:25:05 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// 
static void	print_invalid(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	is_valid_identifier(const char *str)
{
	int i;

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

static int	print_sorted_declarations(char **env)
{
	// Ordenar y mostrar con formato: declare -x VAR="value"
	// Si no es obligatorio el orden, puedes imprimir directamente
	int	i = 0;

	while (env[i])
	{
		printf("declare -x ");
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		else
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}


static int	handle_assignment(char *arg, char **env)
{
	int		len;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
		return (1);
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	key = malloc(len + 1);
	if (!key)
		return (1);
	ft_strlcpy(key, arg, len + 1);
	value = ft_strdup(arg + len + 1);
	if (!!value)
		return (1);
	update_env_var(env, key, value);
	free(key);
	free(value);
	return (0);
}

int	builtin_export(char **args, char **env)
{
	int	i;

	if (!args || !args[0])
		return (1);
	if (!args[1])
		return (print_sorted_declarations(env));
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (handle_assignment(args[i], env))
				print_invalid(args[i]);
		}
		else
		{
			if (!is_valid_identifier(args[i]))
				print_invalid(args[i]);
			else
				update_env_var(env, args[i], NULL);
		}
		i++;
	}
	return (0);
}
