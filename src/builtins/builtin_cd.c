/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:55:51 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/06 17:02:09 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_error(const char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd("no such file or directory: ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static char	*get_env_path(const char *key, char **envp)
{
	int		i;
	size_t	len;

	if (!key || !envp)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	update_env_var(char **env, const char *var_name, const char *value)
{
	char	*env_var;
	int		i;
	int		found;

	env_var = ft_strjoin(var_name, value);
	if (!env_var)
		return (perror("malloc"), 1);
	
	i = 0;
	found = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0 && 
			env[i][ft_strlen(var_name)] == '=')
		{
			free(env[i]);
			env[i] = env_var;
			found = 1;
			break;
		}
		i++;
	}
	if (!found)
	{
		free(env_var);
		return (1);
	}
	return (0);
}

static int	update_pwd_vars(char **env)
{
	char	*old_pwd;
	char	*new_pwd;
	int		ret;

	// Obtener PWD actual antes de cambiar
	old_pwd = get_env_path("PWD", env);
	if (old_pwd)
	{
		// Actualizar OLDPWD con el valor anterior de PWD
		ret = update_env_var(env, "OLDPWD=", old_pwd);
		if (ret != 0)
		{
			// Si no existe OLDPWD, podríamos añadirla al final del env
			// (Código para añadir nueva variable omitido por brevedad)
		}
	}

	// Obtener el directorio actual después del cambio
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), 1);

	// Actualizar PWD con el nuevo directorio
	ret = update_env_var(env, "PWD=", new_pwd);
	free(new_pwd);
	if (ret != 0)
	{
		// Si no existe PWD, podríamos añadirla al final del env
		// (Código para añadir nueva variable omitido por brevedad)
	}
	return (0);
}

static int	go_to_path(char **env, const char *target)
{
	char	*env_path;
	int		ret;

	env_path = get_env_path(target, env); // Obtiene el valor de la variable de entorno
	if (!env_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(" not set", 2);
		return (1); // No se encontró el valor de la variable
	}
	ret = chdir(env_path); // Cambiar al directorio especificado
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_cd(char **args, char **env)
{
	char	*home;

	if (!args[1]) // Si no se pasa argumento, cambiar al directorio HOME
	{
		home = get_env_path("HOME", env);
		if (!home)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		if (chdir(home) == -1)
			return (perror("cd"), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0) // Si el argumento es "-", ir a OLDPWD
	{
		if (go_to_path(env, "OLDPWD") != 0)
			return (1);
		
		// Mostrar el directorio actual cuando usamos cd -
		home = get_env_path("PWD", env);
		if (home)
			ft_putendl_fd(home, 1);
	}
	else // De lo contrario, cambiar al directorio indicado en args[1]
	{
		if (chdir(args[1]) == -1)
		{
			print_error((const char **)args); // Mostrar el error adecuado
			return (1);
		}
	}
	
	// Actualizar PWD y OLDPWD después de un cambio exitoso
	update_pwd_vars(env);
	return (0);
}