/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:55:51 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/21 13:21:44 by marvin           ###   ########.fr       */
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

// Actualiza el valor de una variable de entorno existente
//(como PWD= o OLDPWD=) con un nuevo valor.
// Tambien se usa en el export
int	update_env_var(char **env, const char *var_name, const char *value)
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
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& env[i][ft_strlen(var_name)] == '=')
		{
			free(env[i]);
			env[i] = env_var;
			found = 1;
			break ;
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

// Actualiza las variables PWD y OLDPWD
static int	update_pwd_vars(char **env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_env_path("PWD", env);
	if (old_pwd)
		update_env_var(env, "OLDPWD=", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), 1);
	update_env_var(env, "PWD=", new_pwd);
	free(new_pwd);
	return (0);
}

static int	go_to_path(char **env, const char *target)
{
	char	*env_path;
	int		ret;

	env_path = get_env_path(target, env);
	if (!env_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	ret = chdir(env_path);
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_cd(char **args, t_shell *shell) // JUST CAN HAVE 1 ARG
{
	char	*home;

	if (!args[1])
	{
		home = get_env_path("HOME", shell->env);
		if (!home)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		if (chdir(home) == -1)
			return (perror("cd"), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (go_to_path(shell->env, "OLDPWD") != 0)
			return (1);
		home = get_env_path("PWD", shell->env);
		if (home)
			ft_putendl_fd(home, 1);
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			print_error((const char **)args);
			return (1);
		}
	}
	update_pwd_vars(shell->env);
	return (0);
}
