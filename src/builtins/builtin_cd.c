/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:55:51 by dcampas-          #+#    #+#             */
/*   Updated: 2025/05/22 17:50:40 by dcampas-         ###   ########.fr       */
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
static int	update_pwd_vars(t_shell *shell) //ACUTALIZAR OLDPWD
{
	char	*old_pwd;
	char	*new_pwd;
	int		ret;

	old_pwd = ft_getenv(shell, "PWD");
	if (old_pwd)
	{
		ret = update_env_var(shell->env, "OLDPWD", old_pwd);
		free(old_pwd);
		if (ret != 0)
			return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), 1);
	ret = update_env_var(shell->env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
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

	if (!args[1])
	{
		home = ft_getenv(shell, "HOME");
		if (!home)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		if (chdir(home) == -1)
		{
			free(home);
			return (perror("cd"), 1);
		}
		free(home);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (go_to_path(shell, "OLDPWD") != 0)
			return (1);
		home = ft_getenv(shell, "PWD");
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
	update_pwd_vars(shell);
	return (0);
}
