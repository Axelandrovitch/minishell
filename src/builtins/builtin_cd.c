/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:55:51 by dcampas-          #+#    #+#             */
/*   Updated: 2025/06/05 13:46:59 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_error(const char **args)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(args[1], 2);
}

static int	handle_dash_arg(t_shell *shell, char *current_dir)
{
	char	*pwd;

	if (go_to_path(shell, "OLDPWD") != 0)
	{
		free(current_dir);
		shell->last_exit_status = 1;
		return (1);
	}
	pwd = ft_getenv(shell, "PWD");
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
	}
	return (0);
}

static int	handle_path_arg(char **args, t_shell *shell, char *current_dir)
{
	if (chdir(args[1]) == -1)
	{
		print_error((const char **)args);
		shell->last_exit_status = 1;
		free(current_dir);
		return (1);
	}
	return (0);
}

static int	check_cd_args(t_shell *shell)
{
	int	arg_count;

	arg_count = count_tokens(shell->tokens);
	if (arg_count > 2)
	{
		shell->last_exit_status = 1;
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*current_dir;

	if (check_cd_args(shell) != 0)
		return (1);
	current_dir = getcwd(NULL, 0);
	if (!args[1])
	{
		if (handle_no_args(shell, current_dir) != 0)
			return (1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (handle_dash_arg(shell, current_dir) != 0)
			return (1);
	}
	else
	{
		if (handle_path_arg(args, shell, current_dir) != 0)
			return (1);
	}
	update_pwd_vars(shell, current_dir);
	free(current_dir);
	shell->last_exit_status = 0;
	return (0);
}
