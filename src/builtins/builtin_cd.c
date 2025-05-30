/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:55:51 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/23 12:44:52 by dcampas-         ###   ########.fr       */
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

// Actualiza las variables PWD y OLDPWD
static int	update_pwd_vars(t_shell *shell, char *old_directory)
{
	char	*new_pwd;
	int		ret;

	if (old_directory)
	{
		ret = update_env_var(shell->env, "OLDPWD", old_directory);
		if (ret != 0)
			return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), 1);
	ret = update_env_var(shell->env, "PWD", new_pwd);
	free(new_pwd);
	return (ret);
}

static int	go_to_path(t_shell *shell, const char *target)
{
	char	*env_path;
	int		ret;

	env_path = ft_getenv(shell, (char *)target);
	if (!env_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	ret = chdir(env_path);
	free(env_path);
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
	char	*current_dir;

	if (args[2])
	{

		shell->last_exit_status = 1;
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	}
	current_dir = getcwd(NULL, 0);
	if (!args[1])
	{
		home = ft_getenv(shell, "HOME");
		if (!home)
		{
			free(current_dir);
			shell->last_exit_status = 1;
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		}
		if (chdir(home) == -1)
		{
			free(home);
			free(current_dir);
			shell->last_exit_status = 1;
			return (perror("cd"), 1);
		}
		free(home);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (go_to_path(shell, "OLDPWD") != 0)
		{
			free(current_dir);
			shell->last_exit_status = 1;
			return (1);
		}
		home = ft_getenv(shell, "PWD");
		if (home)
		{
			ft_putendl_fd(home, 1);
			free(home);
		}
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			print_error((const char **)args);
			shell->last_exit_status = 1;
			free (current_dir);
			return (1);
		}
	}
	update_pwd_vars(shell, current_dir);
	free(current_dir);
	shell->last_exit_status = 0;
	return (0);
}
