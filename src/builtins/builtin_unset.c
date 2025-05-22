/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:15:42 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/22 14:25:01 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Muestra un mensaje de error cuando un argumento no es válido.
static void	print_invalid(char *arg)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Busca una variable de entorno y devuelve su índice en el array.
static int	get_env_index(char **env, const char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

// Elimina una variable de entorno de la tabla, desplazando las demás.
static int	remove_env_var(char **env, int index)
{
	int	i;

	if (index < 0)
		return (0);
	free(env[index]);
	i = index;
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	return (0);
}

// Procesa los argumentos y llama a las funciones auxiliares.
int	builtin_unset(char **args, char **env)
{
	int	i;
	int	index;
	int	status;

	if (!args || !args[1] || !env)
		return (0);
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_invalid(args[i]);
			status = 1;
		}
		else
		{
			index = get_env_index(env, args[i]);
			if (index >= 0)
				remove_env_var(env, index);
		}
		i++;
	}
	return (status);
}
